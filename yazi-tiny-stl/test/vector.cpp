#include <iostream>

#include <ttl/digraph.h>
using namespace ttl;

int main()
{
    Digraph g;

    int arr[10] = {2, 4, 8, 1, 5, 6, 9, 3, 0, 7};
    Vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(arr[i]);
    }
    v.show();
    g.draw(v);

    for (auto it = v.begin(); it != v.end(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    for (auto it = v.cbegin(); it != v.cend(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    for (auto it = v.rbegin(); it != v.rend(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    return 0;
}
