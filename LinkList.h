#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include "List.h"
#include "Exception.h"


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
        bool ret = ((0 <= i)  && (i <= m_length));

        if ( ret )
        {
            Node* node = new Node;

            if ( node != NULL)
            {
                Node* current = reinterpret_cast<Node*>(&m_header);

                for (int p = 0; p < i; p++)
                {
                    current = current->next;
                }

                node->value = e;
                node->next = current->next; // 可能从不同的地方插入
                current->next = node;

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
        bool ret = (0 <= i) && (i < m_length); // different

        if ( ret )
        {
            Node* current = reinterpret_cast<Node*>(&m_header);
            
            for (int p = 0; p < i; p++)
            {
                current = current->next;
            }

            Node* toDel = current->next;
            current->next = toDel->next;
            
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
            Node* current = reinterpret_cast<Node*>(&m_header);

            for (int p = 0; p < i; p++)
            {
                current = current->next;
            }

            current->next->value = e;
        }
        
        return ret;
    }

    T get(int i) const
    {
        T ret;

        if ( get(i, ret) )
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsExcetpion, "Invalid parameter i to get element ....");
        }

    }
    bool get(int i, T& e) const
    {
        bool ret = (0 <= i) && (i <= m_length);

        if ( ret )
        {
            Node* current = reinterpret_cast<Node*>(&m_header);

            for (int p = 0; p < i; p++)
            {
                current = current->next;
            }

            e = current->next->value;
        } 

        return ret;
    }
    
    bool length() const 
    {
        return m_length;
    }
    
    void clear()
    {
        while ( m_header.next )
        {
            Node *toDel = m_header.next;
            m_header.next = toDel->next;

            delete toDel;
        }

        m_length = 0;
    }

    ~LinkList()
    {
       clear();
    }

protected:
    struct Node : public Object
    {
        T value;
        Node* next;
    };

    mutable Node m_header; // const成员函数中取地址
    int m_length;  
};

}
#endif // !__LINKLIST_H__