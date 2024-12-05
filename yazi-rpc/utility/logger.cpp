#include <utility/logger.h>
using namespace yazi::utility;

const char * Logger::s_level[LOG_COUNT] =
{
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};

void Logger::open(const string & filename)
{
    m_filename = filename;
    m_ofs.open(filename.c_str(), std::ios::app);    //app表示追加的方式写入
    if (m_ofs.fail())
    {
        throw std::logic_error("open log file failed: " + filename);
    }
    m_ofs.seekp(0, std::ios::end);
    m_len = (int)m_ofs.tellp();     //注意这边长度要重置为0,否则会导致后面翻滚的日志的长度直接继承了之前的日志,就写不进去了
}                                   //但是也不能直接设置成0,因为程序断了重启之后应该接着之前的行号继续,调用这个内置函数即可实现(强转int)

void Logger::close()
{
    m_ofs.close();
}

void Logger::log(Level level, const char* file, int line, const char* format, ...)//这个点点点是c语言可变参数
{
    if (m_level > level)return;
    if (m_ofs.fail())   return;

    std::ostringstream oss;         //这是一个string的流
    time_t ticks = time(nullptr);
    struct tm time_info = {0};
    localtime(&time_info, &ticks);      //转换成秒来操作
    char timestamp[32] = {0};           //这个是time.h里面的和时间配套的函数,把年月日格式化
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &time_info);

    int len = 0;
    const char * fmt = "%s %s %s:%d ";//snprintf第一参是要写入的位置,第二参数是包括空字符的位置
    len = snprintf(nullptr, 0, fmt, timestamp, s_level[level], file, line);//然后后面就是缓冲区的可变参数
    if (len > 0)    //snprintf会返回应该写入的字符串,一开始设置为空就会先预知要写入多少
    {
        char * buffer = new char[len + 1];//就直接new出来用来承接,然后写入oss流缓冲区之后就delete了
        snprintf(buffer, len + 1, fmt, timestamp, s_level[level], file, line);
        buffer[len] = 0;
        oss << buffer;
        m_len += len;
        delete [] buffer;               //这个new是处理固定的东西,下面的new是实际内容
    }

    va_list arg_ptr;                    //这个相当于封装了可变参数列表(即上面...的内容)
    va_start(arg_ptr, format);          //然后应该是把格式化字符串放进来初始化
    len = vsnprintf(nullptr, 0, format, arg_ptr);//然后这边就可以注入了(但这边只是假装注入,实际在下面)
    va_end(arg_ptr);                    //使用完一次这个封装的要释放资源(n内部可能使用了new等)
    if (len > 0)//如果是有效的长度
    {       
        char * content = new char[len + 1];
        va_start(arg_ptr, format);
        vsnprintf(content, len + 1, format, arg_ptr);
        va_end(arg_ptr);
        content[len] = 0;
        oss << content;                 //然后两次写入的东西都进入了oss缓冲区了
        m_len += len;
        delete [] content;
    }

    oss << "\n";
    const string & str = oss.str();

    std::unique_lock<std::mutex> lck(m_mutex);  //这边上个锁,因为多线程会共用一份log单例,
    m_ofs << str;
    m_ofs.flush();

    if (m_console)                      //这边就也会在控制台输出了,如果声明为true
    {
        std::cout << str;
    }

    if (m_max > 0 && m_len >= m_max)
    {
        rotate();
    }
}

void Logger::set_level(int level)
{
    m_level = level;
}

void Logger::set_console(bool console)
{
    m_console = console;
}

void Logger::set_max_size(int size)
{
    m_max = size;
}

void Logger::rotate()
{
    close();            //关闭当前日志
    sleep(1000);        //如果这里不睡眠一秒的话,很可能会导致多个日志在同一秒内就弄满了,导致他们重名
    time_t ticks = time(nullptr);   //获取时间戳
    struct tm time_info = {0};
    localtime(&time_info, &ticks);
    char timestamp[32] = {0};
    strftime(timestamp, sizeof(timestamp), ".%Y-%m-%d_%H-%M-%S", &time_info);
    string filename = m_filename + timestamp;
    if (rename(m_filename.c_str(), filename.c_str()) != 0)//把当前日志改名
    {
        return;                         
    } 
    open(m_filename);               //然后重新启动一个新日志
}

void Logger::sleep(int milliseconds)        //这个sleep考虑了跨平台
{
#ifdef WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

void Logger::localtime(struct tm * time_info, const time_t * ticks)
{
#ifdef WIN32
    localtime_s(time_info, ticks);
#else
    localtime_r(ticks, time_info);
#endif
}
