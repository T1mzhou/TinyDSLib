#ifndef __DYNAMICHEAP_H__
#define __DYNAMICHEAP_H__

#include "DynamicArray.h"
#include "Heap.h"

namespace DSLib
{

template < typename T >
class DynamicHeap : public Heap<T>
{
public:
    DynamicHeap(int capacity, bool isMax = true) : Heap<T>(isNax), m_array(capacity)
    {

    }

    int capacity() const
    {
        return m_array.length();
    }

    void resize(int nc)
    {
        m_array.resize(nc);

        this->m_length = (this->m_length < nc) ? this->m_length : nc;
    }

protected:
    DynamicArray<T> m_array;

    T& get(int i)
    {
        return m_array[i - 1];
    }
};

}

#endif // !__DYNAMICHEAP_H__