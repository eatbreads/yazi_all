#include <iostream>

#include <ttl/digraph.h>
using namespace ttl;

int main()
{
    Digraph g;

    int len = 10;
    int arr[] = {1, 0, 5, 3, 6, 2, 8, 4, 7, 9};

    BSTree<int> t;
    for (int i = 0; i < len; i++)
    {
        std::cout << "add " << arr[i] << std::endl;
        t.add(arr[i]);
//        g.draw(t);
        if (t.valid())
            std::cout << "tree is valid" << std::endl;
        else
            std::cout << "tree is invalid" << std::endl;
    }
    t.show();
//    g.draw(t);

    for (int i = 0; i < 10; i++)
    {
        std::cout << "del " << arr[i] << std::endl;
        t.del(arr[i]);
//        g.draw(t);
        if (t.valid())
            std::cout << "tree is valid" << std::endl;
        else
            std::cout << "tree is invalid" << std::endl;
    }

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
