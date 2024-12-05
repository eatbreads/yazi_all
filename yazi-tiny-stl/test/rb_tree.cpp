#include <iostream>

#include <ttl/digraph.h>
using namespace ttl;

int main()
{
    Digraph g;

    int len = 20;
    int arr[] = {5, 2, 7, 18, 12, 14, 6, 11, 19, 16, 9, 0, 8, 17, 4, 15, 3, 10, 13, 1};
    RBTree<int> t;
    for (int i = 0; i < len; i++)
    {
        t.add(arr[i]);
        g.draw(t);
    }
//    g.draw(t);
    t.show();

    for (auto it = t.begin(); it != t.end(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    for (auto it = t.cbegin(); it != t.cend(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    for (auto it = t.rbegin(); it != t.rend(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    return 0;
}
