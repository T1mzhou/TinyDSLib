#ifndef __CIRCLELIST_H__
#define __CIRCLELIST_H__

#include "CircleList.h"
#include "LinkList.h"

namespace DSLib
{

template <typename T>
class  CircleList : public LinkList<T>
{
public:
    bool insert(const T& e)
    {
        return insert(this->m_length, e);
    }

    bool insert(int i, const T& e)
    {
        bool ret = true;


        return ret;
    }

protected:
    typedef typename LinkList<T>::Node Node;

    Node* last() const
    {
        return this->position(this->m_length - 1)->next;
    }

    void last_to_first() const
    {
        last()->next = this->m_header->next;
    }
};

}
#endif // !__CIRCLELIST_H__