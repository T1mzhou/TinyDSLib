#ifndef __SEQLIST_H__
#define __SEQLIST_H__

namespace DSLib
{

template<typname T>
class SeqList : public list<T>
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
    
    bool set(int i, const T& e);
    bool get(int i, T& e) const;
    int length() const;
    void clear();

    T& operator[] (int i);
    T operator[](int i) const;
    virtual int capacity() const = 0;
protected:
    T* m_array;        // 顺序存储空间
    int m_length;       // 当前线性表长度
}

}

#endif // !__SEQLIST_H__
