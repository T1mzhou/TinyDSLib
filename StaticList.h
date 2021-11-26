#ifndef __STATICLIST_H__
#define __STATICLIST_H__

#include "SeqList.h"

namespace DTLib
{

template < typename T, int N >
class StaticList : public SeqList<T>
{
public:
    StaticList()
    {
        this->m_array = m_space;
        this->m_length = 0;
    }

    int capacity() const
    {
        return N;
    }

protected:
    T m_space[N];
};

}

#endif // !__STATICLIST_H__