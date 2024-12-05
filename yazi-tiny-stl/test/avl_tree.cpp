#include <iostream>

#include <ttl/digraph.h>
using namespace ttl;

int main()
{
    Digraph g;

    int len = 10;
    int arr[] = {2, 4, 8, 1, 5, 6, 9, 3, 0, 7};
    AVLTree<int> t;
    for (int i = 0; i < len; i++)
    {
        std::cout << "add " << arr[i] << std::endl;
        t.insert(arr[i]);
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
