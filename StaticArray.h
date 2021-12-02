#ifndef __STATICARRAY_H__
#define __STATICARRAY_H__

#include "Array.h"

namespace DSLib
{

template < typename T, int N >
class StaticArray : public Array<T>
{
public:
    StaticArray(int capacity)
    {
        this->m_array = m_space;
    }

    StaticArray(const StaticArray<T, N>& obj)
    {
        this->m_array = m_space;
        for (int i = 0; i < N; i++)
        {
            m_array[i] = obj.m_array[i];
        }
    }

    StaticArray<T, N>& operator = (const StaticArray<T, N>& obj)
    {
        if ( this != &obj)
        {
            for (int i = 0; i < N; i++)
            {
                m_space[i] = obj.m_space[i];
            }
        }

        return *this;
    }

    int length() const
    {
        return N;
    }

protected:
    T m_space[N]
};

}

#endif // !__STATICARRAY_H__