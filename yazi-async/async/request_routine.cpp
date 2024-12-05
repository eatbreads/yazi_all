#include <async/request_routine.h>
using namespace yazi::async;

RequestRoutine::RequestRoutine(int sockfd) : Routine(), m_sockfd(sockfd)
{
}

RequestRoutine::~RequestRoutine()
{
}

void RequestRoutine::run()
{
    log_debug("request routine run");
    char buf[1024] = {0};
    Socket client(m_sockfd);
    while (true)
    {
        std::memset(buf, 0, 1024);
        int len = client.recv(buf, 1024);
        if (len < 0)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                // log_debug("socket recv would block: conn=%d", m_sockfd);
                yield();
            }
            else if (errno == EINTR)
            {
                log_debug("socket recv interrupted: conn=%d", m_sockfd);
                yield();
            }
            else
            {
                log_debug("socket connection abort: conn=%d", m_sockfd);
                break;
            }
        }
        else if (len == 0)
        {
            log_debug("socket closed by peer: conn=%d", m_sockfd);
            break;
        }
        else
        {
            log_info("recv: conn=%d data=%s", m_sockfd, buf);
            client.send(buf, strlen(buf));
            yield();
        }
    }
    client.close();
}