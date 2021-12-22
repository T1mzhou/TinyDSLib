#ifndef __DUALCIRCLELIST_H__
#define __DUALCIRCLELIST_H__

#include "DualLinkList.h"
#include "Exception.h"

namespace DSLib
{
template < typename T >

class DualCircleList : public DualLinkList<T>
{
public:
    DualCircleList(int capacity) // 申请空间
    {
        this->m_array = new T[capacity];
        
        if ( this->m_array != NULL )
        {
            this->length = 0;
            this->capacity = capacity;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DualCircleList object ....");
        }

        m_capcacity = capacity;
    }

    int capacity() const
    {
        return m_capcacity;
    }

     ~DualStaticLinkList()
    {
        this->clear(); 
    } 
    
protected:
   
protected:
    int m_capcacity;         // 顺序存储空间的大小
};


}

#endif // !__DUALCIRCLELIST_H__
