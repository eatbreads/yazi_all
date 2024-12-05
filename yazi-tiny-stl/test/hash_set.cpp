#include <iostream>
#include <map>
#include <string>
using std::string;

#include <ttl/hash_set.h>
using namespace ttl;

int main()
{
    HashSet<string> s;
    s.insert("jack");
    s.insert("lucy");
    s.insert("lily");
    s.insert("sean");
    s.show();

    for (auto it = s.begin(); it != s.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "remove jack" << std::endl;
    s.remove("jack");

    for (auto it = s.cbegin(); it != s.cend(); ++it)
    {
        std::cout << *it << std::endl;
    }
    return 0;
}