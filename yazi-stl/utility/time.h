#pragma once

#include <time.h>
#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

namespace yazi
{
    namespace utility
    {
        class Time
        {
        public:
            Time() = default;
            ~Time() = default;

            void start();
            void stop();
            long cost();

        private:
            void get_time_of_day(struct timeval * tv);

        private:
            int m_start_sec = 0;
            int m_start_usec = 0;
            int m_stop_sec = 0;
            int m_stop_usec = 0;
        };
    }
}