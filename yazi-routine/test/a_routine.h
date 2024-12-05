#pragma once

#include <iostream>
#include <routine/routine.h>
using namespace yazi::routine;

class ARoutine : public Routine
{
public:
    ARoutine(int * num) : Routine(), m_num(num) {}
    ~ARoutine()
    {
        if (m_num != nullptr)
        {
            delete m_num;
            m_num = nullptr;
        }
    }

    virtual void run()
    {
        for (int i = 0; i < *m_num; i++)
        {
            std::cout << "a run: num=" << i << std::endl;
            yield(); //要在自己用户态来执行挂起,可以试试注释掉这行的结果
        }
    }

private:
    int * m_num;
};