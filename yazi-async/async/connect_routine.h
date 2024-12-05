#pragma once

#include <socket/socket.h>
using namespace yazi::socket;

#include <routine/routine.h>
#include <routine/schedule.h>
using namespace yazi::routine;

namespace yazi
{
    namespace async
    {
        class ConnectRoutine : public Routine
        {
        public:
            ConnectRoutine() = delete;
            ConnectRoutine(int sockfd);
            ~ConnectRoutine();

            virtual void run();

        private:
            int m_sockfd;
        };
    }
}
