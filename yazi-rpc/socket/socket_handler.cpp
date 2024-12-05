#include <socket/socket_handler.h>
using namespace yazi::socket;

#include <task/task_factory.h>
using namespace yazi::task;

#include <thread/task_dispatcher.h>
using namespace yazi::thread;

void SocketHandler::listen(const string & ip, int port)
{
    m_server = new ServerSocket(ip, port);
}

void SocketHandler::attach(int sockfd)
{
    m_epoll.add(sockfd, (EPOLLIN | EPOLLHUP | EPOLLERR | EPOLLONESHOT));
}

void SocketHandler::detach(int sockfd)
{
    m_epoll.del(sockfd);
}

void SocketHandler::handle(int max_conn, int timeout)
{
    m_epoll.create(max_conn);
    m_epoll.add(m_server->fd(), (EPOLLIN | EPOLLHUP | EPOLLERR));

    while (true)
    {
        int num = m_epoll.wait(timeout); // -1 表示一直等待 
        if (num < 0)
        {
            log_error("epoll wait error: errno=%d errmsg=%s", errno, strerror(errno));
            break;
        }
        else if (num == 0)
        {
            log_debug("epoll wait timeout");
            continue;
        }
        for (int i = 0; i < num; i++)
        {
            if (m_epoll.get_fd(i) == m_server->fd())//表示是监听句柄
            {
                // 服务端套接字可读
                int connfd = m_server->accept();

                // 将连接套接字添加到监听队列
                Socket socket(connfd);
                socket.set_non_blocking();
                attach(connfd);
            }
            else        //表示是通讯句柄
            {
                int connfd = m_epoll.get_fd(i);
                detach(connfd);
                if (m_epoll.is_set(i, EPOLLHUP))            //句柄断了
                {
                    // 连接套接字挂断了
                    log_error("socket hang up by peer: conn=%d", connfd);
                    ::close(connfd);
                }
                else if (m_epoll.is_set(i, EPOLLERR))       //好像是其他error
                {
                    log_error("socket error: conn=%d", connfd); 
                    ::close(connfd);
                }
                else if (m_epoll.is_set(i, EPOLLIN))        //表示通信句柄发来东西了
                {
                    auto task = TaskFactory::create(connfd);
                    Singleton<TaskDispatcher>::instance()->assign(task);    //把task分配给线程池
                }
            }
        }
    }
}