#include <iostream>

#include <ttl/digraph.h>
using namespace ttl;

int main()
{
    Digraph g;

    int arr[10] = {2, 4, 8, 1, 5, 6, 9, 3, 0, 7};
    Heap<int> h;
    for (int i = 0; i < 10; i++)
    {
        h.push(arr[i]);
        g.draw(h);
    }

    for (int i = 0; i < 10; i++)
    {
        h.pop();
        g.draw(h);
    }

    h.show();

    return 0;
}
