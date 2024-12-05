#include <iostream>
#include <string>
using std::string;

#include <utility/timer.h>
using namespace yazi;

#include <timer/timer_manager.h>
using namespace yazi::timer;


void foo()
{
    std::cout << "foo" << std::endl;
}

void bar(const string & name)
{
    std::cout << "bar:" << name << std::endl;
}

int main()
{
   utility::Timer t;
   t.start(1000, foo);

   utility::Timer t2;
   t2.start(1000, bar, "hello");

   std::getchar(); // 阻塞等待输入，保持程序运行

    // auto mgr = Singleton<TimerManager>::instance();
    // mgr->schedule(1000, foo);
    // mgr->schedule(2000, 3, bar, "kitty");
    // while (true)
    // {
    //     mgr->update();
    // }
    return 0;
}