#include <utility/timer.h>
using namespace yazi::utility;
                //ps:这边原子变量可以直接在构造函数内部初始化
Timer::Timer() : m_active(false), m_period(0), m_repeat(-1)
{
}

Timer::Timer(int repeat) : m_active(false), m_period(0), m_repeat(repeat)
{
}

Timer::~Timer()         //即虽然线程被detach了,但是主线程析构thread的时候也会执行析构
{                       //导致这个线程最后会退出
    stop();   
}
 
void Timer::stop()
{ 
    m_active.store(false);
}
