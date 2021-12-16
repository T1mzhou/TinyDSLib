#ifndef __SHAREDPOINTER_H__
#define __SHAREDPOINTER_H__

#include "Pointer.h"
#include "Exception.h"

#include <cstdlib>

namespace DSLib
{

template< typename T >
class SharedPointer : public Pointer<T>
{
public:
    SharedPointer(T* p = NULL) : m_ref(NULL)
    {
        if (p != NULL)
        {
            this->m_ref = static_cast<int*>((std::malloc(sizeof(int))));
            if (this->m_ref != NULL)
            {
                *(this->m_ref) = 1;
                this->m_pointer = p;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create SharedPointer Object ....");
            }
        }

    }

    SharedPointer(const SharedPointer<T>& obj) : Pointer<T>(NULL)
    {
        assign(obj);  
    }

    SharedPointer<T>& operator= (const SharedPointer<T>& obj)
    {
         if ( this != &obj )
        {
            clear();
            assign(obj);  
        }
    }

    void clear()
    {
        T* toDel = this->m_pointer;
        int* ref = this->m_ref;

        this->m_pointer = NULL;
        this->m_ref = NULL;

        if ( ref )
        {
            (*ref)--;

            if ( *ref == 0 )
            {
                free(m_ref);
                delete toDel;
            }
        }
    }

    ~SharedPointer()
    {
        clear();
    }

protected:
    void assign(const SharedPointer<T>& obj)
    {
        this->m_pointer = obj.m_pointer;
        this->m_ref = obj.m_ref;
            
        if ( this->m_ref != NULL )
        {
            (*this->m_ref)++;
        }
    }

protected:
    int* m_ref;
};

template < typename T >
bool operator == (const SharedPointer<T>& lhs, const SharedPointer<T>& rhs)
{
    return (lhs.get() == rhs.get());
}

template < typename T >
bool operator != (const SharedPointer<T>& lhs, const SharedPointer<T>& rhs)
{
    return (lhs.get() != rhs.get());
}

}

#endif // !__SHAREDPOINTER_H__

