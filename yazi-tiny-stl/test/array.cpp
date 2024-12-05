#include <iostream>

#include <ttl/digraph.h>
using namespace ttl;

int main()
{
    Digraph g;

    int arr[10] = {2, 4, 8, 1, 5, 6, 9, 3, 0, 7};
    Array<int, 10> a;
    for (int i = 0; i < 10; i++)
    {
        a[i] = arr[i];
    }
    a.show();
    g.draw(a);

    for (auto it = a.begin(); it != a.end(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    for (auto it = a.cbegin(); it != a.cend(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    for (auto it = a.rbegin(); it != a.rend(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    return 0;
}
