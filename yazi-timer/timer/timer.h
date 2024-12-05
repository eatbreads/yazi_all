#pragma once

#include <chrono>
#include <functional>

namespace yazi
{
    namespace timer
    {
        class Timer
        {
            friend class TimerManager;
        public:
            Timer();
            Timer(int repeat);

            template <typename F, typename... Args>
            void callback(int milliseconds, F && f, Args&&... args);

            void on_timer();

        private:
            static int64_t now();

        private:
            int64_t m_time;      //m_time是下一次要执行的时间
            std::function<void()> m_func;
            int m_period;       // 一个周期时间
            int m_repeat;       //重复次数
        };

        template <typename F, typename... Args> 
        void Timer::callback(int milliseconds, F && f, Args&&... args)
        {
            m_period = milliseconds;
            m_func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        }
    }
}