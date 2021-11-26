#ifndef __DYNAMICLISH_H__
#define __DYNAMICLISH_H__

#include "SeqList.h"
#include "Exception.h"

namespace DSLib
{

template < typename T >
class DynamicList : public SeqList<T>
{
public:
    DynamicList(int capacity) // 申请空间
    {
        this->m_array = new T[capacity];
        
        if ( this->m_array != NULL )
        {
            this->length = 0;
            this->capacity = capacity;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynameicList object ....");
        }

        m_capcacity = capacity;
    }

    int capacity() const
    {
        return m_capcacity;
    }

    void resize(int capacity) // 重新设置顺序存储空间得大小
    {
        if (capacity != m_capcacity )
        {
            T* array = new T[capacity]; // 为了保证异常安全，所以这么处理
            
            if ( array != NULL )
            {
                int length = (this->m_length < capacity ?  this->m_length ： capacity);
                for (int i = 0; i < length; i++)
                {
                    array[i] = this->m_array[i]; // 可能会发生异常，没关系，没有影响原来对象
                }

                T* temp = this->m_array;
                this->m_array = array;
                this->length = length;
                this->capacity = capacity;

                delete[] temp; // 触发析构函数的调用，为了避免在析构后函数里面抛出异常后，
                               // 后面的赋值操作失效，所以使用temp，而不是直接delete[] m_array;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to resize DynameicList Object ... ");
            }
        }
    }

    ~DynamicList()            // 归还空间
    {
        delete[] this->m_array;
    }

protected:
    int m_capcacity;         // 顺序存储空间的大小
};

}

#endif // !__DYNAMICLISH_H__
