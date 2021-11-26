#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include "List.h"
#include "Exception.h"


namespace DSLib
{

template < typename T >
class SeqList : public List<T>
{
public:
    bool insert(int i, const T& e)
    {
        bool ret = ( 0 <=i ) && (i <= m_length);
        ret = ret && (m_length < capacity());
        
        if ( ret )
        {
            for (int pos = m_length - 1; pos > i; pos--)
            {
                m_array[pos + 1] = m_array[pos]; 
            }

            m_array[i] = e;

            m_length++;
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = (0 <= i) && (i < m_length);

        if ( ret )
        {
            for (int pos = i; pos < m_length - 1; pos++)
            {
                m_array[pos] = m_array[pos + 1];
            }

            m_length--;
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        bool ret = (0 <= i) && (i < m_length);

        if ( ret )
        {
            m_array[i] = e;
        }

        return ret;
    }

    bool get(int i, T& e) const
    {
        bool ret = (0 <=i ) && (i < m_length);

        if ( ret )
        {
            e = m_array[i];
        }

        return ret;
    }

    int length() const
    {
        return m_length;
    }

    void clear()
    {
        m_length = 0;
    }

    T& operator[] (int i)
    {
        bool ret = (0 <=i ) && (i < m_length);

        if ( ret )
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalide ...");
        }
    }

    T operator[] (int i) const
    {
        return (const_cast<SeqList<T>&>(*this))[i]; // 调用上个非const版本
    }
    
    virtual int capacity() const = 0;
protected:
    T* m_array;         // 顺序存储空间
    int m_length;       // 当前线性表长度
};

}

#endif // !__SEQLIST_H__
