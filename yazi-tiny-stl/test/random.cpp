#include <iostream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <vector>

int main()
{
    // generate random sequence integer array for test
    srand(time(0));

    int len = 10;
    std::vector<int> arr;
    std::map<int, bool> maps;
    while (true)
    {
        int n = rand() % len;
        auto it = maps.find(n);
        if (it == maps.end())
        {
            arr.push_back(n);
            maps[n] = true;
        }
        if ((int)arr.size() == len)
        {
            break;
        }
    }

    std::cout << "int arr[] = {";
    for (int i = 0; i < len; i++)
    {
        int n = arr[i];
        if (i != 0)
        {
            std::cout << ", ";
        }
        std::cout << n;
    }
    std::cout << "};";
    std::cout << std::endl;

    return 0;
}
