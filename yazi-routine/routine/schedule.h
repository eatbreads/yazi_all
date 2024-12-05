#pragma once

#include <list>
#include <routine/routine.h>

namespace yazi
{
    namespace routine
    {
        class Schedule
        {
            friend class Routine;       //记得声明为友元,这样routinue就能访问总栈的东西
        public:
            Schedule();
            ~Schedule();

            void create(int stack_size);
            void append(Routine * r);
            bool empty() const;
            int size() const;

            void run();

        private:
            ucontext_t m_main;
            char * m_stack;
            int m_stack_size;
            std::list<Routine *> m_queue;
        };
    }
}
