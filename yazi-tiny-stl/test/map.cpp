#include <iostream>

#include <ttl/avl_tree.h>
#include <ttl/map.h>
using namespace ttl;

int main()
{
    Map<int, int> m;
    m[123] = 123;
    for (int i = 0; i < 10; i++)
    {
        m.insert(Pair<int, int>(i, i * 10));
    }

    for (auto it = m.begin(); it != m.end(); ++it)
    {
        std::cout << it->first << " -> " << it->second << std::endl;
    }

    for (auto it = m.cbegin(); it != m.cend(); ++it)
    {
        std::cout << it->first << " -> " << it->second << std::endl;
    }

    return 0;
}