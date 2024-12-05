#include <routine/routine.h>
#include <routine/schedule.h>
using namespace yazi::routine;

Routine::Routine() : m_status(RT_READY), m_stack(nullptr), m_stack_size(0), m_s(nullptr)
{
}

Routine::~Routine()
{
    if (m_stack != nullptr)
    {
        delete [] m_stack;
        m_stack = nullptr;
        m_stack_size = 0;
    }
}

void Routine::resume()
{
    switch (m_status)
    {
        case RT_READY://就绪态的话,就保存上下文之后,跳入m_ctx的上下文执行(这个下面其实还是在main函数的协程里执行)
        {
            getcontext(&m_ctx);
            m_ctx.uc_stack.ss_sp = m_s->m_stack;        //这里就是指向栈底,给协程运行时候存储上下文,这是调度器的总栈
            m_ctx.uc_stack.ss_size = m_s->m_stack_size;
            m_ctx.uc_stack.ss_flags = 0;                //不懂这是啥,置0即可
            m_ctx.uc_link = &(m_s->m_main);             //m_s->m_main就是main函数上下文结构体,因为schedule是在main函数创建的
            m_status = RT_RUNNING;                          //这个1表示参数个数为1
            makecontext(&m_ctx, (void (*)(void))Routine::func, 1, this);    //然后设置新的入口函数fun(成员函数要传入this指针)
            swapcontext(&(m_s->m_main), &m_ctx);            //然后main函数保存上下文,执行能力切换给当前工作函数
            break;
        }
        case RT_SUSPEND://如果是挂起态,就会把当前协程栈东西拷贝到总栈里面,就是说不能直接被运行,需要从挂起态把上下文
        {               //放入总栈才变成运行态
            std::memcpy(m_s->m_stack + m_s->m_stack_size - m_stack_size, m_stack, m_stack_size);
            m_status = RT_RUNNING;
            swapcontext(&(m_s->m_main), &m_ctx);        //开始运行
            break;
        }
        default:
            break;
    }
}

void Routine::yield()       //主动保存当前上下文,然后跳回main函数
{
    char dummy = 0;
    // 栈由高地址向低地址增长, 这里判断栈是否溢出
    assert(m_s->m_stack + m_s->m_stack_size - &dummy <= m_s->m_stack_size);
    if (m_stack_size < m_s->m_stack + m_s->m_stack_size - &dummy)//这里是用户栈爆了
    {//<左边的size是当前栈的size,右边的是总栈的大小减去当前栈帧顶部(&dummy),如果空间还够就可以把当前
     //总栈放进这个局部栈里面ps:其实就相当于把总栈分割成了一堆局部协程栈(用户栈)
        if (m_stack != nullptr)//进到if了说明空间合适
        {
            delete [] m_stack;
            m_stack = nullptr;
        }
        m_stack_size = m_s->m_stack + m_s->m_stack_size - &dummy;
        m_stack = new char[m_stack_size];       //然后new出来之后
    }                                   //-----------dummy,other,other,other,即为高地址向低地址,所以从dummy往后面拷贝
    std::memcpy(m_stack, &dummy, m_stack_size);//把总栈的内容拷贝进用户栈,会覆盖上一次保存的上下文(所以都是从首地址开始)
    m_status = RT_SUSPEND;                      //设置为挂起
    m_s->append(this);
	swapcontext(&m_ctx, &(m_s->m_main));        //然后切换回main(调度器),同时保存当前上下文
}

int Routine::status()
{
    return m_status;
}

void Routine::func(void * ptr)
{
    auto r = (Routine *)ptr;
    r->run();
    delete r;
}
