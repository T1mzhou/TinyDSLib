#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include "List.h"


namespace DSLib
{

template < typename T >
class LinkList : public List<T>
{
public:
    LinkList()
    {
        m_header->next = NULL;
        m_length = 0;
    }

    bool insert(const T& e)
    {
        insert(m_length, e);
    }

    bool insert(int i, const T& e)
    {
        bool ret = (0 <= i()  && (i <= m_length);

        if ( ret )
        {
            Node* node = new Node;

            if ( node != NULL)
            {
                Node* ret = reinterpret_cast<Node*>(&m_header);

                for (int p = 0; p < i; p++)
                {
                    ret = ret->next;
                }

                node->value = e;
                node->next = NULL;
                
                ret->next = node;

                m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element ...");
            }
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = (0 <= i) && (i <= m_length);

        if ( ret )
        {
            Node* node = reinterpret_cast<Node*>(&m_header);
            
            for (int p = 0; p < i; p++)
            {
                node = node->next;
            }

            Node* toDel = node->next;
            node->next = toDel->next;
            
            delete toDel;

            m_length--;
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        bool ret = (0 <= i) && (i < m_length); // different

        if ( ret )
        {   
            Node* node = reinterpret_cast<Node*>(&m_header);

            for (int p = 0; p < i; p++)
            {
                node = node->next;
            }

            node->next->value = e;
        }
        
        return ret;
    }

    bool get(int i, T& e)
    {
        bool ret = (0 <= i) && (i <= m_length);

        if ( ret )
        {
            Node* node = reinterpret_cast<Node*>(&m_header);

            for (int p = 0; p < i; p++)
            {
                node = node->next;
            }

            e = node->next->value;
        } 

        return ret;
    }
    
    bool length() const 
    {
        return m_length;
    }
    
    void clear()
    {
       ~LinkList();
    }

    ~LinkList()
    {
        while ( m_header->next )
        {
            Node *toDel = m_header->next;
            m_header->next = toDel->next;

            delete toDel;
        }

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