#ifndef __STATICSTACK_H__
#define __STATICSTACK_H__

#include "Stack.h"
#include "Exception.h"

namespace DSLib
{

template < typename T, int N >
class StaticStack : public Stack<T>
{
public:
    StaticStack()
    {
        m_stop = -1;
        m_size = 0;
    }

    int capacity() const
    {
        return N;
    }

    virtual void push(const T& e)
    {
       if ( m_size < N )
       {
           m_spack[top + 1] = e; // 为了异常安全,e可以为类,可能发生异常,所以先赋值后进行++操作
           m_top++;
           m_size++;
       }
       else
       {
           THROW_EXCEPTION(InvalidOperationException, "No Space in current stack ....");
       }
    }

    void  pop()
    {
        if ( m_size > 0 )
        {
            m_top--;
            m_size--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No Space in current stack ....");
        }
    }

    T top()
    {
        if ( m_size > 0 )
        {
            return m_space[m_top];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No Space in current stack ....");
        }
    }

    void clear()
    {
        m_top = -1;
        m_size = 0;
    }

    int size() const
    {
        return m_size;
    }

protected:
    T m_space[N];
    int m_size;
    int m_top;
};

}
#endif // !__STATICSTACK_H__