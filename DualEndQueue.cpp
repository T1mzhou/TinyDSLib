#ifndef __DUALENDQUEUE_H__
#define __DUALENDQUEUE_H__

#include "LinkQueue.h"

namespace DSLib
{
template < typename T >
class DualEndQueue : public LinkQueue<T>
{
public:
    void push(const T& e)
    {
        Node* node = new Node();

        if ( node != NULL )
        {
            node->value = e;

            list_add(&node->head, &this->m_header);

            this->m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to add new element ...");
        }
    }

    void dismiss()
    {
        if( this->m_length > 0 )
        {
            list_head* toDel = this->m_header.prev;
            
            list_del(toDel->prev);
            
            this->m_length--;

            delete list_entry(toDel, Node, head);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current dualendqueue ...");
        }
    }

    T back() const
    {
        if ( this->m_length > 0 )
        {
        	return list_entry(this->m_header.prev, Node, head)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current dualendqueue ...");
        }
    }

private:
    typedef typename LinkQueue<T>::Node Node;
};

};

#endif // !__DUALENDQUEUE_H__