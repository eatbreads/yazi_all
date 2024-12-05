#include <iostream>

#include <routine/schedule.h>
using namespace yazi::routine;

#include <test/a_routine.h>
#include <test/b_routine.h>

int main()
{
    Schedule s;
    s.create(1024 * 64);

    int * num1 = new int(5);
    auto a = new ARoutine(num1);
    s.append(a);

    int * num2 = new int(10);
    auto b = new BRoutine(num2);
    s.append(b);

    s.run();
    return 0;
}
