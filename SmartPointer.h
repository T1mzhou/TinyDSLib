#ifndef __SMARTPOINTER_H__
#define __SMARTPOITNER_H__

#include "Object.h"
#include "pointer.h"

namespace DSLib
{
template < typename T >

class SmartPointer : public Pointer<T>
{
public:
   SmartPointer(T* p = NULL) : Pointer<T>(p)
   {

   }

    SmartPointer(const SmartPointer<T>& obj)
    {
        this->m_pointer = obj.m_pointer;
        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
    }

    SmartPointer<T>& operator=(const SmartPointer<T>& obj)
    {
        if (this != &obj)
        {
            T* p = m_pointer; // 异常安全

            this->m_pointer = obj.m_pointer;

            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;

            delete p;
        }

        return *this;
    }

    ~SmartPointer()
    {
        delete this->m_pointer;
    }

protected:
    T* m_pointer;
};
}

#endif // !__SMARTPOINTER_H__
