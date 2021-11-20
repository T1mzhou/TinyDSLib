#include <iostream>
#include "SmartPointer.h"

using namespace DSLib;

class Test
{
public:
    Test()
    {
        std::cout << "构造" << std::endl;
    }

    ~Test()
    {
        std::cout << "析构" << std::endl;
    }
};

int main()
{
    SmartPointer<Test> p = new Test();
    
    return 0;
}