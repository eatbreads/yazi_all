#pragma once

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <mutex>
#include <string>
using std::string;

#include <ctime>
#include <cstdarg>
//这边考虑了跨平台的操作
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <utility/singleton.h>

namespace yazi
{
    namespace utility
    {   //这个第一参会匹配到对应的等级下标的数组,就不用手动转化成string再写入了
        #define log_debug(format, ...) \
            Singleton<Logger>::instance()->log(Logger::LOG_DEBUG, __FILE__, __LINE__, format, ##__VA_ARGS__)

        #define log_info(format, ...) \
            Singleton<Logger>::instance()->log(Logger::LOG_INFO, __FILE__, __LINE__, format, ##__VA_ARGS__)

        #define log_warn(format, ...) \
            Singleton<Logger>::instance()->log(Logger::LOG_WARN, __FILE__, __LINE__, format, ##__VA_ARGS__)

        #define log_error(format, ...) \
            Singleton<Logger>::instance()->log(Logger::LOG_ERROR, __FILE__, __LINE__, format, ##__VA_ARGS__)

        #define log_fatal(format, ...) \
            Singleton<Logger>::instance()->log(Logger::LOG_FATAL, __FILE__, __LINE__, format, ##__VA_ARGS__)

        class Logger
        {
            SINGLETON(Logger);
 
        public:
            enum Level
            {
                LOG_DEBUG = 0,
                LOG_INFO,
                LOG_WARN,
                LOG_ERROR,
                LOG_FATAL,
                LOG_COUNT           //小技巧,同之前的语言管理器的枚举,都是在编译期确定的大小
            };

            void open(const string & filename);
            void close();                                         //这个...就是c语言的可变参数
            void log(Level level, const char* file, int line, const char* format, ...);
            void set_level(int level);
            void set_console(bool console);
            void set_max_size(int bytes);

        private:
            void rotate();                  //日志翻滚的函数,在内部把当前日志变成备份日志(备份日志会带时间戳),当前日志没有时间戳,会不断有日志变成当前日志
            void sleep(int milliseconds);   //下面这俩时间操作和睡眠操作考虑了跨平台的操作
            void localtime(struct tm * time_info, const time_t * ticks);

        private:
            string m_filename;
            std::ofstream m_ofs;
            int m_max = 0;              //表示日志默认的大小,如果是0就是不支持翻滚的意思
            int m_len = 0;
            int m_level = LOG_DEBUG;
            bool m_console = true;       //这个表示是否也在控制台输出       
            static const char * s_level[LOG_COUNT];//这玩意被初始化为等级的string,便于写入,索引就是等级对应的int
            std::mutex m_mutex;
        };
    }
}
