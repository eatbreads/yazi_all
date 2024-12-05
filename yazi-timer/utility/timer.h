#pragma once

#include <thread>
#include <atomic>
#include <functional>

namespace yazi
{
    namespace utility
    {
        class Timer
        {
        public:
            Timer();
            Timer(int repeat);
            ~Timer();

            template <typename F, typename ...Args>
            void start(int milliseconds, F && func, Args&&... args);
            void stop();

        private:
            std::thread m_thread;
            std::atomic<bool> m_active;
            std::function<void()> m_func;
            int m_period; // milliseconds
            int m_repeat;
        };

        template <typename F, typename ...Args>
        void Timer::start(int milliseconds, F && f, Args&&... args)
        {
            if (m_active.load())    //使用load读取原子变量的值
            {
                return;             //即这个start只能在未激活的时候使用
            }
            m_period = milliseconds;
            m_func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
            m_active.store(true);   //使用这个更新原子变量的值
            m_thread = std::thread([&]() {
                if (m_repeat < 0)
                {
                    while (m_active.load())//这个lambda就是循环执行function函数,如果repeat一开始小于0就会一直执行
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(m_period));
                        if (!m_active.load())
                        {
                            return;
                        }
                        m_func();
                    }
                }
                else
                {
                    while (m_repeat > 0)//这边是大于零就会执行n次就结束了
                    {
                        if (!m_active.load())
                        {
                            return;
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(m_period));
                        if (!m_active.load())
                        {
                            return;
                        }
                        m_func();
                        m_repeat--;
                    }
                }
            });     //设置detach是在主线程,thread被
            m_thread.detach();      //这个线程设置为分离的,使得主线程无法管他(合理,定时器就是应该不受其他干扰的)
        }
    }
}