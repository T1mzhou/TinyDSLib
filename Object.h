#ifndef __OBJECT_H__
#define __OBJECT_H__

namespace DSLib
{

class Object
{
public:
    void* operator new (unsigned int size) throw();
    void operator delete (void *p);
    void *operator new[] (unsigned int size) throw();
    void operator delete[] (void* p);
    virtual ~Object() = 0;
};

}
#endif // !__OBJECT_H__