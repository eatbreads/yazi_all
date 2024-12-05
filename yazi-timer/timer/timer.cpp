#include <timer/timer.h>
using namespace yazi::timer;

Timer::Timer() : m_period(0), m_repeat(-1)
{
    m_time = now();
}

Timer::Timer(int repeat) : m_period(0), m_repeat(repeat)
{
    m_time = now();
}

void Timer::on_timer()
{
    if (!m_func || m_repeat == 0)       //这里是等于0,即初始化为-1或者更小的就相当于可以执行一次
    {
        return;
    }
    m_func();
    m_time += m_period;         //把下次到时时间加一下
    if (m_repeat > 0)
    {                           //这边把次数减一下
        m_repeat--;
    }
}

int64_t Timer::now()
{
    // 获取当前时间戳
    auto now = std::chrono::system_clock::now();

    // 将时间戳转换为毫秒数
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    return now_ms.time_since_epoch().count();
}