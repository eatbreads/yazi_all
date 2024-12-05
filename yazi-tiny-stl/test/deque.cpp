#include <iostream>

#include <ttl/digraph.h>
using namespace ttl;

int main()
{
    Digraph g;

    int arr[10] = {2, 4, 8, 1, 5, 6, 9, 3, 0, 7};
    Deque<int> q;
    for (int i = 0; i < 10; i++)
    {
        q.push_back(arr[i]);
        g.draw(q);
    }
//    g.draw(q);
    q.show();

    for (auto it = q.begin(); it != q.end(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    for (auto it = q.cbegin(); it != q.cend(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    for (auto it = q.rbegin(); it != q.rend(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    return 0;
}
