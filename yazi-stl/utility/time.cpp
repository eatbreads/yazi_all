#include <utility/time.h>
using namespace yazi::utility;

void Time::start()
{
    struct timeval tv;
    get_time_of_day(&tv);
    m_start_sec = tv.tv_sec;
    m_start_usec = tv.tv_usec;
}

void Time::stop()
{
    struct timeval tv;
    get_time_of_day(&tv);
    m_stop_sec = tv.tv_sec;
    m_stop_usec = tv.tv_usec;
}

long Time::cost()
{
    long time_diff = (m_stop_sec - m_start_sec) * 1000000 + (m_stop_usec - m_start_usec);
    return time_diff;
}

void Time::get_time_of_day(struct timeval * tv)
{
#ifdef WIN32
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    struct tm tm;
    tm.tm_year = wtm.wYear - 1900;
    tm.tm_mon = wtm.wMonth - 1;
    tm.tm_mday = wtm.wDay;
    tm.tm_hour = wtm.wHour;
    tm.tm_min = wtm.wMinute;
    tm.tm_sec = wtm.wSecond;
    tm. tm_isdst  = -1;
    time_t clock = mktime(&tm);
    tv->tv_sec = clock;
    tv->tv_usec = wtm.wMilliseconds * 1000;
#else
    gettimeofday(tv, nullptr);
#endif
}