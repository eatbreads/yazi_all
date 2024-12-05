#include <iostream>
#include <functional>
#include <vector>
#include <string>
using std::string;

#include <ttl/digraph.h>
using namespace ttl;

int main()
{
    Digraph g;

    std::vector<string> v;
    v.push_back("hello");
    v.push_back("kitty");
    v.push_back("world");
    v.push_back("yes");
    v.push_back("no");
    v.push_back("lucy");
    v.push_back("lily");
    v.push_back("jack");
    v.push_back("sean");

    HashTable<string> h;
    for (auto & item : v)
    {
        h.insert(item);
        g.draw(h);
    }

    h.show();
//    g.draw(h);

    for (auto it = h.begin(); it != h.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;

    for (auto it = h.cbegin(); it != h.cend(); ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;

    return 0;
}