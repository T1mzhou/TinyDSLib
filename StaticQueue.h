#ifndef __STATICQUEUE_H__
#define __STATICQUEUE_H__

#include "Queue.h"
#include "Exception.h"

namespace DSLib
{

template < typename T, int N >
class StaticQueue : public Queue<T>
{
public:
    StaticQueue()
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }

    int capacity() const{
        return N;
    }

    void add(const T& e)
    { 
        if ( m_length < N )
        {
            m_space[m_rear] = e;
            m_rear = (m_rear + 1) % N;
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No space in current queue ....");
        }
    }
    
    void remove()
    {
        if ( m_length > 0 )
        {
            m_front = (front + 1)  % N;
            m_length--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No Element in current queue ....");
        }
    }

    T front() const
    {
        if ( m_length > 0)
        {           
            return m_space[m_front];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No Element in current queue ....");
        }

    }

    void clear()
    {
        
        m_front = -1;
        m_rear = -1;
        m_length = 0
        
    }
   
    int length() const 
    {
        return m_length;
    }

protected:
    T m_space[N];
    int m_front;
    int m_rear;
    int m_length;
};

}
#endif // !__STATICQUEUE_H__
