#ifndef __DYNAMICARRAY__
#define __DYNAMICARRAY__

#include "Array.h"
#include "Exception.h"

namespace DSLib
{

template < typename T >
class DynamicArray : public Array<T>
{
public:
    DynamicArray(int length)
    {
        this->m_array = new T[length];

        if ( this-> m_array != NULL )
        {
            m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memeroy to create DynamicArray Object ...");
        }
    }

    DynamicArray(const DynamicArray<T>& obj)
    {
        this->m_array = new T[obj.m_length];
        
        if ( this->m_array != NULL )
        {
            this->m_length = obj.m_length;

            for (int i = 0; i < obj.m_length; i++)
            {
                this->m_array[i] = obj.m_array[i];
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray objecdt ....");
        }
    }

    DynamicArray<T>& operator = (const DynamicArray<T>& obj)
    {
        if ( this != &obj )
        {
            T* array = new T[obj.m_length];
        
            if ( array != NULL )
            {
                for (int i = 0; i < obj.m_length; i++)
                {
                    array[i] = obj.m_array[i];
                }

                T* temp = this->m_array;

                this->m_array = array;
                this->m_length = obj.m_length;

                delete[] temp; // 异常安全
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray objecdt ....");
            }
        }

        return *this;
    }

    int length() const
    {
        return m_length;
    }

    void resize(int length)
    {
        
        if ( length != m_length)
        {
            T* array = new T[length];

            if ( array != NULL )
            {
                int size = (length < m_length) ? length : m_length;

                for (int i = 0; i < size; i++)
                {
                    array[i] = this->m_array[i];
                }

                T* temp = this->m_array;
               
                this->m_array = array;
                this->m_length = length;

                delete[] temp;
            }
        }

        return ;
    }

    ~DynamicArray()
    {
        delete[] this->m_array;
    }

protected:
    int m_length;
};

}

#endif // !__DYNAMICARRAY__
