#include <iostream>

#include <ttl/digraph.h>
using namespace ttl;

int main()
{
    Digraph g;

    int arr[10] = {2, 4, 8, 1, 5, 6, 9, 3, 0, 7};
    Queue<int> q;
    for (int i = 0; i < 10; i++)
    {
        q.push(arr[i]);
        g.draw(q);
    }
    q.show();

    return 0;
}
