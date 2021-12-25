#ifndef __LINKSTACK_H__
#define __LINKSTACK_H__

#include "Stack.h"
#include "LinkList.h"
#include "Exception.h"

namespace DSLib
{

template < typename T >
class LinkStack : public Statck<T>
{
public:
    void push(const T& e)
    {
        m_list.insert(0, e);
    }

    void pop()
    {
        if ( m_list.length() > 0 )
        {
            m_list.remove(0);
        }
        else
        {
             THROW_EXCEPTION(InvalidOperationException, "No Element in current stack ....");
        }
    }

    T top() const
    {
        if ( m_list.length() > 0 )
        {
            return m_list.get(0);
        }
        else
        {
             THROW_EXCEPTION(InvalidOperationException, "No Element in current stack ....");
        }
    }

    void clear()
    {
        m_list.clear();
    }

    int size() const{
        return m_list.length();
    }

protected:
    LinkList<T> m_list;
};

}
#endif // !__LINKSTACK_H__