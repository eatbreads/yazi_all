#include <iostream>

#include <ttl/digraph.h>
using namespace ttl;

int main()
{
    Digraph g;

    int len = 20;
    int arr[] = {5, 2, 7, 18, 12, 14, 6, 11, 19, 16, 9, 0, 8, 17, 4, 15, 3, 10, 13, 1};
//    int len = 50;
//    int arr[] = {1, 2, 45, 29, 49, 19, 35, 41, 27, 46, 20, 34, 10, 17, 7, 5, 37, 22, 25, 8, 40, 36, 13, 12, 3, 18, 42, 9, 43, 24, 33, 23, 4, 0, 21, 11, 15, 32, 47, 26, 6, 30, 39, 48, 31, 14, 28, 38, 44, 16};

//    int len = 100;
//    int arr[] = {88, 22, 59, 74, 50, 0, 49, 37, 61, 13, 41, 76, 54, 25, 19, 69, 58, 85, 95, 60, 21, 66, 64, 6, 87, 99, 47, 40, 33, 67, 43, 20, 27, 80, 16, 52, 35, 55, 30, 56, 73, 4, 45, 36, 93, 26, 23, 51, 91, 86, 98, 17, 10, 72, 68, 12, 44, 65, 83, 70, 31, 39, 3, 53, 5, 24, 79, 97, 18, 48, 82, 81, 14, 62, 71, 28, 8, 89, 2, 9, 11, 92, 32, 42, 96, 90, 94, 77, 75, 15, 63, 84, 1, 46, 57, 7, 78, 34, 29, 38};
    BBTree<int, 3> t;
    for (int i = 0; i < len; i++)
    {
        t.insert(arr[i]);
    }
    g.draw(t);

//    for (int i = 0; i < len; i++)
//    {
//        std::cout << "remove " << arr[i] << std::endl;
//        t.remove(arr[i]);
//        g.draw(t);
//    }

    t.remove(5);

    t.traverse();
    std::cout << std::endl;

    if (t.valid())
    {
        std::cout << "bb tree is valid" << std::endl;
    }
    else
    {
        std::cout << "bb tree is invalid" << std::endl;
    }
    g.draw(t);

    for (auto it = t.begin(); it != t.end(); it++)
    {
        std::cout << (*it) << ", " << std::flush;
    }
    std::cout << std::endl;

    return 0;
}