#include <iostream>

#include <stl/array.h>
using namespace whao::stl;

int main()
{
    Array<int, 10> a;
    int cnt = 0;
    for (auto it = a.begin(); it != a.end(); it ++)
        *it = ++ cnt; 
    for (auto it = a.rbegin(); it != a.rend(); ++ it)
        std::cout << *it << ", ";
    std::cout << std::endl;
    return 0;
}
