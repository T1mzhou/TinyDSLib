#ifndef __STACK_H__
#define __STACK_H__

#include "Object.h"

namespace DSLib
{

template < typename T >
class Statck : public Object
{
public:
    virtual void push(const T& e) = 0;
    virtual void pop() = 0;
    virtual T top() const = 0;
    virtual void clear() = 0;
    virtual int size() const = 0;
};

}

#endif // !__STACK_H__