#ifndef __HEAP_H__
#define __HEAP_H__

#include "Queue.h"
#include "Exception.h"

namespace DSLib
{

template < typename T >
class Heap : public Queue<T>
{
    Heap(bool isMax)
    {
        m_isMax = isMax;
        m_length = 0;
    }

    void add(const T& e)
    {

        int i = length() + 1;

        if ( i <= capacity() )
        {
            while ( (i > 1) && compare(e, get(parent(i))) )
            {
                get(i) = get(parent(i));

                i = parent(i);
            }

            get(i) = e;

            m_length++;
        }

    }

    T front() const
    {
        if ( length() > 0 )
        {
            return get(1);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "Heap is empty ...");
        }
    }

    bool front(T& e) const
    {
        bool ret = (length() > 0);

        if ( ret )
        {
            e = get(i)
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "Heap is empty ...");
        }
    }

    void remove()
    {
        if ( length() > 1 )
        {
            T& e = get(length());
            int i = 1;
            int ci = left(i);

            while ( ci < length() )
            {
                if ( ((ci + 1) < length()) && compare(get(ci + 1), get(ci)) )
                {
                    ci++;
                }

                if ( !compare(get(ci), e) )
                {
                    break;
                }
                else
                {
                    get(i) = get(ci);
                    i = ci;
                    ci = left(i);
                }
            }

            get(i) = e;
            m_length--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "Heap is empty ...");
        }

    }

    int length()
    {
        return m_length;
    }

    void clear()
    {
        m_length = 0;
    }

    virtual int capacity() const = 0;

protected:

    virtual bool compare(const T& lv, const T& rv)
    {
        return m_isMax ? (lv > rv) : (lv < rv);
    }
    
    virtual T& get(int i) const = 0;

    T& get(int i) const
    {
        return const_cast< Heap<T>* >(this)->get(i);
    }

    int left(int i) const
    {
        return 2 * i;
    }

    int right(int i) const
    {
        return 2 * i + 1;
    }

    int parent(int i) const
    {
        return i / 2;
    }

protected:
    bool m_isMax;
    int m_length;
};

}

#endif // !__HEAP_H__