#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "Object.h"

namespace DSLib
{

template < typename T >
class Queue : public Object
{
public:
    virtual void add(const T& e) = 0;
    virtual void remove() = 0;
    virtual T front() const = 0;
    virtual void clear() = 0;
    virtual int length() const = 0;
};

}
#endif // !__QUEUE_H__