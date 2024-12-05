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
        case RT_READY:
        {
            getcontext(&m_ctx);
            m_ctx.uc_stack.ss_sp = m_s->m_stack;
            m_ctx.uc_stack.ss_size = m_s->m_stack_size;
            m_ctx.uc_stack.ss_flags = 0;
            m_ctx.uc_link = &(m_s->m_main);
            m_status = RT_RUNNING;
            makecontext(&m_ctx, (void (*)(void))Routine::func, 1, this);
            swapcontext(&(m_s->m_main), &m_ctx);
            break;
        }
        case RT_SUSPEND:
        {
            std::memcpy(m_s->m_stack + m_s->m_stack_size - m_stack_size, m_stack, m_stack_size);
            m_status = RT_RUNNING;
            swapcontext(&(m_s->m_main), &m_ctx);
            break;
        }
        default:
            break;
    }
}

void Routine::yield()
{
    char dummy = 0;
    // 栈由高地址向低地址增长, 这里判断栈是否溢出
    assert(m_s->m_stack + m_s->m_stack_size - &dummy <= m_s->m_stack_size);
    if (m_stack_size < m_s->m_stack + m_s->m_stack_size - &dummy)
    {
        if (m_stack != nullptr)
        {
            delete [] m_stack;
            m_stack = nullptr;
        }
        m_stack_size = m_s->m_stack + m_s->m_stack_size - &dummy;
        m_stack = new char[m_stack_size];
    }
    std::memcpy(m_stack, &dummy, m_stack_size);
    m_status = RT_SUSPEND;
    m_s->append(this);
	swapcontext(&m_ctx, &(m_s->m_main));
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
