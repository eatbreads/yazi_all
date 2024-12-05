#include <iostream>
#include <utility/option.h>
using namespace yazi::utility;

// 短参数测试   ./main -a -b 123 -cjack
// int main(int argc, char *argv[])
// {
//     Option opt;
//     opt.add("a", Option::OPT_NO);
//     opt.add("b", Option::OPT_REQUIRED);
//     opt.add("c", Option::OPT_OPTIONAL); 

//     opt.parse(argc, argv);

//     opt.show();

//     bool a = opt.get("a");
//     int b = opt.get("b");
//     string c = opt.get("c");
//     std::cout << "a=" << a << ",b=" << b << ",c=" << c << std::endl;

//     return 0;
// }


// 长参数测试       ./main --name jack --age=18 --gender
int main(int argc, char *argv[])
{
    Option opt;
    opt.add("name", Option::OPT_REQUIRED);
    opt.add("age", Option::OPT_OPTIONAL);
    opt.add("gender", Option::OPT_OPTIONAL);

    opt.parse(argc, argv);

    opt.show();

    string name = opt.get("name");
    int age = opt.get("age");
    int gender = opt.get("gender");
    std::cout << "name=" << name << ",age=" << age << ",gender=" << gender << std::endl;

    return 0;
}
