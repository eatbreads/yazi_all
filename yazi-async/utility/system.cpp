#include <utility/system.h>
using namespace yazi::utility;

#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/resource.h>

#include <utility/logger.h>
#include <utility/ini_file.h>
using namespace yazi::utility;

void System::init()
{
    core_dump();        //就是使得可以吐核
    m_root_path = get_root_path();      //拿到当前路径

    const string & dir = m_root_path + "/log";  //生成一个log文件
    DIR * dp = opendir(dir.c_str());        //打开目录
    if (dp == nullptr)
    {
        mkdir(dir.c_str(), 0755);
    }
    else
    {
        closedir(dp);
    }
}

// System 类中的 core_dump 函数
void System::core_dump()
{
    // 声明一个 rlimit 结构体 x,这个好像是库里面的东西
    struct rlimit x;

    // RLIM_INFINITY 表示资源限制 (在此例中为 core 文件大小) 被设置为无限
    x.rlim_cur = RLIM_INFINITY;         //就是说对这俩都设置成无限制
    x.rlim_max = RLIM_INFINITY;

    // 调用 setrlimit 函数，将 RLIMIT_CORE 作为资源类型，并传入 x 结构体的地址
    // setrlimit 函数用来设置指定资源的限制
    setrlimit(RLIMIT_CORE, &x);     //然后用这个宏开放core
}

string System::get_root_path()
{
    if (!m_root_path.empty())
    {
        return m_root_path;
    }
    char path[1024] = {0};
    int len = readlink("/proc/self/exe", path, 1024);//用这个来获取当前可执行文件的路径
    if (len < 0 || len >= 1024)// 如果 readlink 调用不成功，或者返回的长度小于 0 或大于等于 1024，则返回空字符串
    {
        return "";
    }
    for (int i = len; i >= 0; --i)// 反向迭代 path 数组，从 len 开始
    {
        if (path[i] == '/')
        {
            path[i] = '\0';// 找到第一个 '/' 字符并将其置为 '\0'，以将路径截断到上一级目录
            break;
        }
    }
    return path; // 返回根路径
}
