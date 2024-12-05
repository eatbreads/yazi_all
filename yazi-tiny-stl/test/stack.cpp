#include <iostream>

#include <ttl/digraph.h>
using namespace ttl;

int main()
{
    Digraph g;

    int arr[10] = {2, 4, 8, 1, 5, 6, 9, 3, 0, 7};
    Stack<int> s;
    for (int i = 0; i < 10; i++)
    {
        s.push(arr[i]);
        g.draw(s);
    }

    for (int i = 0; i < 10; i++)
    {
        s.pop();
        g.draw(s);
    }
    s.show();

    return 0;
}
