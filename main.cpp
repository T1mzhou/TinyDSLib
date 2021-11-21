#include <iostream>
#include "SmartPointer.h"
#include "Exception.h"

using namespace std;
using namespace DSLib;


int main()
{
    try
    {
        throw Exception("test", __FILE__, __LINE__);
    }
    catch(const Exception& e)
    {
        cout << "catch(const Exception& e)" << endl;
        cout << e.message() << endl;
        cout << e.location() << endl;
    }

    return 0;
}