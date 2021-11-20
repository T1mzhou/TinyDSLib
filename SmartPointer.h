#ifndef __SMARTPOINTER_H__
#define __SMARTPOINTER_H__

namespace DSLib
{
template<typename T>

class SmartPointer
{
public:
    SmartPointer(T* p = nullptr)
    {
        m_pointer = p;
    }

    SmartPointer(const SmartPointer<T>& obj)
    {
        m_pointer = obj.m_pointer;
        const_cast<SmartPointer<T>&>(obj).m_pointer = nullptr; 
    }

    SmartPointer<T>& operator=(const SmartPointer<T>& obj)
    {
        if (this != &obj)
        {
            delete m_pointer;
            m_pointer = nullptr;
            m_pointer = obj.m_pointer;
            const_cast<SmartPointer<T>&>(obj).m_pointer = nullptr;
        }
      
        return *this;
    }

    bool isNull()
    {
        return (m_pointer == nullptr);
    }

    T* get()
    {
        return m_pointer;
    }

    T& operator*()
    {
        return *m_pointer;
    }

    T* operator->()
    {
        return m_pointer;
    }

    ~SmartPointer()
    {
        delete m_pointer;
        m_pointer = nullptr;
    }

protected:
    T* m_pointer;    
};

}
#endif // !__SMARTPOINTER_H__