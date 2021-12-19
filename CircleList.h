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

        i = i % (this->length + 1); 

        ret = LinkList<T>::insert(i, e);

        if ( ret && (0 == i) )
        {
            last_to_first();
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = true;

        i = mod(i)

        if (0 == i)
        {
            Node* toDel = this->m_header.next;

            if ( toDel != NULL)
            {
                this->m_header.next = toDel->next;
                this->m_length--;

                if ( this->m_length > 0 )
                {
                    last_to_first();

                    if ( this->m_current == toDel )
                    {
                        this->current = toDel->next;
                    }
                }
                else
                {
                    this->m_header.next = NULL;
                    this->m_current = NULL;
                }

                this->destory(toDel);
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = LinkList<T>::remove(i);
        }    

        return ret;
    }

    bool set(int i, const T& e)
    {
        return LinkList<T>::set(mod(i), e);
    }

    T get(int i) const
    {
        reutrn LinkList<T>::get(mod(i));
    }

    T get(int i, const T& e) const
    {
        return LinkList<T>::get(mod(i), e);
    }

    int find(const T& e) const
    {
        int ret = -1;

        // last()->next = NULL; // 改成单链表，导致不够异常安全
        // ret = LinkList<T>::find(e); // 导致不够异常安全
        // last_to_first();
        
        Node* slider = this->m_header.next;

        for (int i = 0; i < this->m_length; i++)
        {
            if ( slider->value == e ) // 抛出异常不影响
            {
                ret = i;
                break;
            }

            slider = slider->next;
        }

        return ret;
    }

    void clear()
    {
        if ( this->m_length > 0 )
        {
            // last()->next = NULL;
            // LinkList<T>::clear(); //发生异常后，循环链表就成了单链表

            while ( this->m_length > 1 )
            {
                remove(1); // remove 0会导致大量的移动
            }

            if ( 1 == this->m_length)
            {
                Node* toDel = this->m_header.next;

                this->head.next = NULL;
                this->m_length = 0;
                this->m_current = NULL;

                this->destroy(toDel);
            }
        }
    }

    bool move(int i ,int step)
    {
        return LinkList<T>::move(mod(i), step);
    }

    bool end()
    {
        return (this->m_length == 0) || (this->m_current == NULL);
    }

    ~CircleList()
    {
        clear();
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

    int mod(int i) const
    {
        return (this->m_length == 0) ? 0 : (i % this->length); 
    }
};

}
#endif // !__CIRCLELIST_H__