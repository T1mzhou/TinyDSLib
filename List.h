#ifndef __LIST_H__
#define __LIST_H__

#include "Object.h"

namespace DSLib 
{

template < typename T >
class List : public Object
{
public:
    virtual bool insert(const T& e) = 0;
    virtual bool insert(int i, const T& e) = 0;
    virtual bool remove(int i) = 0;
    virtual bool set(int i, const T& e) = 0;
    virtual bool get(int i, T& e) const = 0;
    virtual int length()  const = 0;
    virtual void clear() = 0;

public:
    List() { } 
protected:
    List(const List&);
    List& operator= (const List&);
};


}

#endif // !__LIST_H__
