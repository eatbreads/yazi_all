#include <iostream>

#include <ttl/avl_tree.h>
#include <ttl/set.h>
using namespace ttl;

int main()
{
    Set<int> s;
    for (int i = 0; i < 10; i++)
    {
        s.insert(i);
    }

    for (auto it = s.begin(); it != s.end(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    for (auto it = s.cbegin(); it != s.cend(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    return 0;
}