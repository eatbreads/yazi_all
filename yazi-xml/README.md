# yazi-xml
a tiny c++ xml parser


## example

```c++
#include <iostream>
using namespace std;

#include <xml/xml.h>
using namespace yazi::xml;

int main()
{
    Xml root;
    root.load("./test.xml");

    const string & name = root["student"]["name"].text();
    int id = root["student"].attr("id");
    const string & age = root["student"]["age"].text();
    for (Xml::iterator it = root.begin(); it != root.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    return 0;
}
```