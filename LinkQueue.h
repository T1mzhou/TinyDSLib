#ifndef __LINKQUEUE_H__
#define __LINKQUEUE_H__

#include "Queue.h"
#include "LiuxList.h"
#include "Exception.h"

namespace DSLib
{

template < typename T >
class LinkQueue : public Queue<T>
{
public:
    LinkQueue()
    {
        m_length = 0;
        INIT_LIST_HEAD(&m_header);
    }

    void add(cosnt T& e) // O(n)->O(1)
    {
        Node* node = new Node();
        if ( node != NULL )
        {
            node->value = e;
            list_add_tail(node);
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No memeory to add new element.... ");
        }
    }
    
    void remove()
    {
        if ( m_length > 0 )
        {
            list_head* toDel = m_header.next;

            list_del(toDel);
            m_length--;

            delete list_entry(toDel, Node, head);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No Element in current LinkQueue ....");
        }
    }
    
    T front() const
    {
        if (  m_length > 0 )
        {
            return list_entry(m_header.next, Node, head)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No Element in current LinkQueue ....");
        }
    }
    
    void clear()
    {
        while ( m_length > 0 )
        {
            remove()
        }
    }
    
    int length() const
    {
        return m_length;
    }

    ~LinkQueue()
    {
        clear();
    }

protected:
    struct Node : public Object
    {
        list_head head;
        T value;
    };

    list_head m_header;
    int m_length ;
};

]
#endif // !__LINKQUEUE_H__