#include <rpc/server.h>
using namespace yazi::rpc;

#include <frame/server.h>

void Server::start()
{
    try
    {
        Singleton<yazi::frame::Server>::instance()->start();
    }
    catch (std::exception & e)      //这里可能会抛出异常,注意一下
    {
        std::cout << e.what() << std::endl;
    }
}
 