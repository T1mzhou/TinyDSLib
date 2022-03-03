#ifndef __STATICHEAP_H__
#define __STATICHEAP_H__

#include "StaticArray.h"
#include "Heap.h"

namespace  DSlib
{

template < typename T, int N >
class StaticHeap : public Heap<T>
{
public:
    StaticHeap(bool isMax = true) : Heap<T>(isMax)
    {

    }

    int capacity() const
    {
        return N;
    }

protected:
    StaticArray<T, N> m_array;

    T& get(int i)
    {
        return m_array[i - 1];
    }
};


} // namespace  DSlib

#endif // !__STATICHEAP_H__#define 