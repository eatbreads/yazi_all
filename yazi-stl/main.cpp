#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <utility/time.h>
using namespace yazi::utility;

#include <stl/vector.h>
using namespace yazi::stl;

int main()
{
    Time t;
    t.start();

    const int max = 1000000;
    Vector<int> v;
    for (int i = 0; i < max; i++)
    {
        v.push_back(i);
    }

    t.stop();
    long us = t.cost();
    std::cout << us / 1000.0 / max << "ms" << std::endl;

    return 0;
}
