#ifndef __DUALINKLIST_H__
#define __DUALINKLIST_H__

#include "LinkList.h"
#include "Exception.h"

namespace DSLib
{
template < typename T >

class DualLinkList : public List<T>
{

public:
    DualLinkList()
    {
        m_header.next = NULL;
        m_header.pre = NULL;
        m_length = 0;
        m_step = 1;
        m_current = NULL;
    }

    bool insert(const T& e) 
    {
        return insert(m_length, e);
    }

    bool insert(const int i, const T& e)
    {
        bool ret = ((0 <= i) && (i <= m_length));

        if ( ret )
        {
            Node* node = create();
            if ( node != NULL )
            {
                Node* current = position(i);
                Node* next = current->next;
                
                node->value = e;

                node->next = next;
                current->next = node;
                
                if ( current != reinterpret_cast<Node*>(&m_header))
                {
                    node->pre  = current;
                }
                else
                {
                    node->pre = NULL;

                }

                if ( next != NULL )
                {
                    next->pre = node;
                }

                m_length++;
            }
            else
            {
                HROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element ...");
            }
        }
    }

    bool remove(int i)
    {
         bool ret = ((0 <= i) && (i < m_length));

         if ( ret )
         {
            Node* current = position(i);
            Node* toDel = current->next;
            Node* next = toDel->next;

            if ( m_current == toDel )
            {
                m_current = next;
            }

            current->next = next;

            if ( next != NULL )
            {
                next->pre = current;
            }

            m_length--;
            
            destroy(toDel);
         }
    }

     bool set(int i, const T& e)
    {
        bool ret = (0 <= i) && (i < m_length); // different

        if ( ret )
        {   
            position(i)->next->value = e;
        }
        
        return ret;
    }

    virtual T get(int i) const
    {
        T ret;

        if ( get(i, ret) )
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter i to get element ....");
        }

    }

    bool get(int i, T& e) const
    {
        bool ret = (0 <= i) && (i <= m_length);

        if ( ret )
        { 
            e = position(i)->next->value;
        } 

        return ret;
    }
    
    bool length() const 
    {
        return m_length;
    }

    int find(const T& e) const
    {
        int ret = -1;
        int i = 0;
        
        Node* node = m_header->next;

        while ( node.isNull() )
        {
            if ( node->value == e )
            {
                ret = i;
                break;
            }
            else
            {
                node = node->next;
                i++;
            }
        }

        return ret;
    }

    virtual void clear()
    {
        while ( m_length > 0 )
        {
            remove(0);
        }
    }

     virtual bool move(int i, int step = 1)
    {
        bool ret = ((0 <= i) && (i < length()) && (step >= 0));

        if ( ret )
        {
            m_current = position(i)->next;
            m_step = step;
        }
    }

    virtual bool end()
    {
        return (m_current == NULL);
        // return m_current.isNull();
    }

    virtual T current()
    {
        if ( m_current != NULL )
        {
            if ( !end() )
            {
                return m_current->value;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value at current position ....");
            }
        }
    }

    virtual bool next()
    {
        int i = 0;

        while ( (i < m_step) && !end() )
        {
            m_current = m_current->next;
            i++;
        }

        return (i == m_step);  
    }

    virtual bool pre()
    {
        int i = 0;

        while ( (i < m_step) &&  !end() )
        {
            m_current = m_current->pre;
            i++;
        }

        return (i == m_step);  
    }

    ~DualLinkList()
    {
        clear();
    }

protected:
    Node* position(int i) const
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);

        for (int p = 0; p < i; p++)
        {
            ret = ret->next;
        }

        return ret;
    }

    virtual Node* create()
    {
        return new Node();
    }

    virtual void destory(Node* pn)
    {
        delete pn;
    }

protected:
    struct Node : public Object {
        T value;
        Node* next;
        Node* pre;
    };

    mutable struct : public Object {
        char reserved[sizeof(T)];
        Node* next;
        Node* pre;
    }m_header;
};

}

#endif // !__DUALINKLIST_H__
