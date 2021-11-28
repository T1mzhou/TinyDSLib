#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "Object.h"
#include "Exception.h"

namespace DSLib
{

template < typename T >
class Array : public Object
{
public:
    virtual bool set(int i, const T& e)
    {
        bool ret = ((0 <= i) && (i < length()));

        if ( ret )
        {
            m_array[i] = e;
        }

        return ret;
    }

    virtual bool get(int i, T& e) const
    {
        bool ret = ((0 <= i) && (i < length()));

        if ( ret )
        {
            e = m_array[i];
        }

        return ret;
    }

    T& operator[] (int i)
    {
        if ((0 < i) && (i < length()))
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Paramter i is invalide ...");
        }
    }

    T operator[](int i) const
    {
        return (const_cast<Array<T>&>(*this))[i];
    }

    virtual int length() const = 0;

protected:
    T* m_array;
};

}

#endif // !__ARRAY_H__