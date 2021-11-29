#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include "List.h"


namespace DSLib
{

template < typename T >
class LinkList : public List<T>
{
public:
    LinkList();

    virtual bool insert(const T& e) = 0;
    virtual bool insert(int i, const T& e) = 0;
    virtual bool remove(int i) = 0;
    virtual bool set(int i, const T& e) = 0;
    virtual bool get(int i, T& e) = 0;
    virtual bool length() const = 0;
    virtual void clear()
    {
        m_length = 0;
    }

protected:
    struct Node : public Object
    {
        T value;
        Node* next;
    };

    Node m_header;
    int m_length;  
};

}
#endif // !__LINKLIST_H__