#include <iostream>

#include <ttl/digraph.h>
using namespace ttl;

int main()
{
    Digraph g;

    int arr[10] = {2, 4, 8, 1, 5, 6, 9, 3, 0, 7};
    SkipList<int, 4> l;
    for (int i = 0; i < 10; i++)
    {
        l.insert(arr[i]);
        g.draw(l);
    }
    l.show();
//    g.draw(l);

    for (auto it = l.begin(); it != l.end(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    for (auto it = l.cbegin(); it != l.cend(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    return 0;
}
