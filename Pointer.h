#ifndef __POINTER_H__
#define __POINTER_H__

namespace DSLib
{
template < typename T >
class Pointer : public Object
{
public:
    Pointer(T* p = NULL);
    {
        m_pointer = p;
    }

    T* operator-> (){
        return m_pointer;
    }

    T& operator* ()
    {
        return *m_pointer;
    }
    bool isNull()
    {
        return (m_pointer == NULL);
    }
    T* get()
    {
        return m_pointer;
    }

protected:
    T* m_pointer;

};

}

#endif // !__POINTER_H__
