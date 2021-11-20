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
    SmartPointer<Test> sp = new Test();
    SmartPointer<Test> nsp;

    nsp = sp;
    // nsp++; error: no ‘operator++(int)’ declared for postfix ‘++’ [-fpermissive
    std::cout << sp.isNull() << std::endl;
    std::cout << nsp.isNull() << std::endl;

    return 0;
}