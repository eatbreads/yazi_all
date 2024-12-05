#pragma once
#include <iostream>
#include <string>
using std::string;

#include <ctime>
#ifdef WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

namespace yazi
{
    namespace utility
    {
        class Time
        {
        public:
            Time();
            ~Time() = default;

            int year() const;
            int month() const;
            int day() const;
            int hour() const;
            int minute() const;
            int second() const;
            int week() const;

            int seconds() const;
            int64_t milliseconds() const;
            int64_t operator - (const Time & other) const;

            // format = "%Y-%m-%d %H:%M:%S"
            string format(const string & format) const;

            static void sleep(int milliseconds);

            void show() const;

        private:
            void get_local_time(struct tm * tm, const time_t * ticks);
            void get_time_of_day(struct timeval * tv);

        private:
            struct tm m_tm = {0};
            int m_sec = 0;
            int m_usec = 0;
        };
    }
}