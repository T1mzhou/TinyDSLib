#ifndef __LINKQUEUE_H__
#define __LINKQUEUE_H__

#include "Queue.h"
#include "LinkList.h"
#include "Exception.h"

namespace DSLib
{

template < typename T >
class LinkQueue : public Queue<T>
{
public:
    void add(cosnt T& e)
    {
        m_list.insert(e);
    }
    
    void remove()
    {
        if ( m_list.length() > 0 )
        {
            m_list.remove(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No Element in current LinkQueue ....");
        }
    }
    
    T front() const
    {
        if ( m_list.length() > 0 )
        {
            m_list.get(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No Element in current LinkQueue ....");
        }
    }
    
    void clear()
    {
        m_list.clear();
    }
    
    int length() const
    {
        return m_list.length();
    }

protected:
    LinkList<T> m_list;
};

]
#endif // !__LINKQUEUE_H__