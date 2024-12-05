#include <iostream>

#include <ttl/digraph.h>
using namespace ttl;

int main()
{
    Digraph g;

    Trie<std::string> t;
    t.insert("foo");
    t.insert("foot");
    t.insert("food");
    t.insert("foobar");
    t.insert("football");
    t.insert("foolish");
    t.insert("boy");
//    g.draw(t);

    for (auto it = t.begin(); it != t.end(); it++)
    {
        std::cout << *it << std::endl;
    }
//
//    for (auto it = t.cbegin(); it != t.cend(); it++)
//    {
//        std::cout << *it << std::endl;
//    }

//    for (auto it = t.rbegin(); it != t.rend(); ++it)
//    {
//        std::cout << *it << std::endl;
//    }

//    std::cout << t.search("fo") << std::endl;
//    std::cout << t.prefix("fo") << std::endl;
//
//    t.remove("foot");
//    g.draw(t);
//    std::cout << t.search("foo") << std::endl;
//    std::cout << t.search("foot") << std::endl;
//    std::cout << t.search("foobar") << std::endl;
//    t.remove("football");
//    g.draw(t);
//    std::cout << t.search("football") << std::endl;

    //    Trie<int> t;
//    t.insert(123);
//    t.insert(126);
//    t.insert(1268);
//    t.insert(1248);
//    t.insert(-123);
//    g.draw(t);


    return 0;
}
