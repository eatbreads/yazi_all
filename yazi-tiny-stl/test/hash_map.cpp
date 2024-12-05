#include <iostream>
#include <map>
#include <string>
using std::string;

#include <ttl/digraph.h>
using namespace ttl;

int main()
{
    Digraph g;

    HashMap<string, int> m;
    m.insert(Pair<string, int>("jack", 18));
    m.insert(Pair<string, int>("lucy", 20));
    m.insert(Pair<string, int>("lily", 22));
    m.insert(Pair<string, int>("sean", 30));
    m["chen"] = 38;
    m.show();
    g.draw(m);

    for (auto it = m.begin(); it != m.end(); ++it)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    m.remove("jack");

    std::cout << m.at("lucy") << std::endl;

    for (auto it = m.cbegin(); it != m.cend(); ++it)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    std::cout << m.search("jack") << std::endl;
    return 0;
}