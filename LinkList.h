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
        m_current = NULL;
        m_step = 1;
    }

    Node* position(int i) const
    {
         Node* current = reinterpret_cast<Node*>(&m_header);
            
        for (int p = 0; p < i; p++)
        {
            current = current->next;
        }

        return current;
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
            Node* node = create();

            if ( node != NULL)
            {
                Node* current = position(i);

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
            Node* current = position(i);

            Node* toDel = current->next;

            if ( m_current == toDel )
            {
                m_current = toDel->next;    // fixbug修改游标指向合法的数据
            }

            current->next = toDel->next;

            m_length--; // fix bug add 异常安全性
            destroy(toDel);

            // m_length--;

           
        }

        return ret;
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

    T get(int i) const
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

        while ( node )
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
    
    void clear()
    {
        while ( m_header.next )
        {
            Node *toDel = m_header.next;
            m_header.next = toDel->next;
            
            m_length--;     // fixbug 异常安全
            destroy(toDel);
        }

        // m_length = 0;
    }

    bool move(int i, int step = 1)
    {
        bool ret = ((0 <= i) && (i < length()) && (step >= 0));

        if ( ret )
        {
            m_current = position(i)->next;
            m_step = step;
        }
    }

    bool end()
    {
        return (m_current == NULL);
    }

    T current()
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

    bool next()
    {
        int i = 0;

        while ( (i < m_step) && (!end() )
        {
            m_current = m_current->next;
            i++;
        }

        return (i == m_step);  
    }

    ~LinkList()
    {
       clear();
    }

protected:
    virtual Node* create()
    {
        return new Node();
    }

    virtual void destroy(Node* pn)
    {
        delete pn;
    }

protected:
    struct Node : public Object
    {
        T value;
        Node* next;
    };

    mutable struct : public Object // const成员函数中取地址
    {
        char reserved[sizeof(T)]; // 内存布局相同
        Node* next;
    } m_header;                   

    Node* m_current;
    int   m_step;

    int m_length;  
};

}
#endif // !__LINKLIST_H__