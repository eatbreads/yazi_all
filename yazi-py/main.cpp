#include <iostream>

#include <py/python.h>
using namespace yazi::py;

int main()
{
    auto py = Python();
    py.run("import sys");
    py.run("sys.path.append('./../script')");

    try
    {
        Module module("test3");
        Class cls(module, "Person");
        Object obj(cls, "jack", 20);
        Function func(obj, "foo");
        auto result = func.call<bool>();
    }
    catch (std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}