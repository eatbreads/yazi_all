#pragma once

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <ucontext.h>

namespace yazi
{
    namespace routine
    {
        class Schedule;//Schedule是引入了当前头文件,所以我们前置声明即可(我们无法再引入Schedule头文件)

        class Routine
        {
            friend class Schedule;
        public:
            enum Status
            { 
                RT_READY = 0,
                RT_RUNNING,
                RT_SUSPEND
            };

            Routine();
            virtual ~Routine();

            virtual void run() = 0;

            void resume();
            void yield();
            int status();

        protected:
            static void func(void * ptr);       //这个是入口函数

        private:
            ucontext_t m_ctx;
            int m_status;               
            char * m_stack;             //一般都是用char,这样子指针移动就是1字节
            int m_stack_size;           //局部栈大小
            Schedule * m_s;             //调度器,内部有总栈
        };
    }
}
