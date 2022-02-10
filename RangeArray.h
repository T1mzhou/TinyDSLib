#ifndef __RANGEARRAY_H__
#define __RANGEARRAY_H__

#include "Array.h"

namespace DSLib
{
template< typename T >
class RangeArray : public Array<T>
{
public:
    RangeArray(int lower, int upper)
    {
        this->m_array = new T[upper - lower + 1];

        m_lower = lower;
        m_upper = upper;
    }

    RangeArray(const RangeArray<T>& obj)
    {
        int len = obj.length();
        this->array = new T[len];

        for (int i = 0; i < len; i++)
        {
            this->m_array[i] = obj[i];
        }

        this->m_lower = obj.m_lower;
        this->m_upper = obj.m_upper;
        
    }

    RangeArray<T>& operator= (const RangeArray<T>& obj)
    {
        if ( this = &obj )
        {
            int len = obj.length();
            T* toDel = this->m_array;
            T* arr = new T[len];

            for (int i = 0; i < len; i++)
            {
                arr[i] = obj.m_array[i];
            }

            m_lower = obj.m_lower;
            m_upper = obj.m_upper;

            this->m_array = arr;

            delete[] toDel;
        }

        return *this;
    }

    bool set(int i, const T& e)
    {
        bool ret = ((m_lower <= i) && (i <= m_upper));

        if ( ret )
        {
            this->m_array[i - m_lower] = e;
        }
        
        return ret;
    }

    virtual bool get(int i, T& e)
    {
        bool ret = ((m_lower <= i) && (i <= m_upper));

        if ( ret )
        {
            e = this->m_array[i - m_lower];
        }

        return ret;
    }

    virtual T& operator[] (int i)
    {
        bool ret = ((m_lower <= i) && (i <= m_upper));

        if ( ret )
        {
            return this->m_array[i - m_lower];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
        }
    }

    virtual T operator[] (int i) const
    {
        return (const_cast<RangeArray<T>&>(*this))[i];
    }

    int lower() const
    {
        return m_lower;
    }

    int upper() const
    {
        return m_upper;
    }

    int length() const
    {
        return (m_upper - m_lower + 1);
    }

    ~RangeArray()
    {
       
        delete[] this->m_array;
    }

protected:
    int m_lower;
    int m_upper;
};

}

#endif // !__RANGEARRAY_H__