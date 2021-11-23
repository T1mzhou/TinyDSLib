#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include "Object.h"

namespace DSLib
{

#define THROW_EXCEPTION(e, m)  (throw e(e, __FILE__, __LINE__))

class Exception : public Object
{
public:
    Exception(const char* message);
    Exception(const char* file, int line);
    Exception(const char* message, const char* file, int line);

    Exception(const Exception& e);
    Exception& operator=(const Exception& e);

    virtual const char* message() const;
    virtual const char* location() const;

    virtual ~Exception() = 0;       

protected:
    void init(const char* message, const char* file, int line);

    char* m_message;
    char* m_location;
};

class ArithmeticException : public Exception
{
    ArithmeticException(const char* message) : Exception(message)  { }
    ArithmeticException(char* file, int line) : Exception(file, line) { }
    ArithmeticException(const char* message, const char* file, int line) : Exception(message, file, line) { }
    ArithmeticException(const ArithmeticException& e) :  Exception(e) { }
    ArithmeticException& operator=(const ArithmeticException& e)
    {
        Exception::operator=(e);
        return *this;
    }
};

class NullPointerException : public Exception
{
    NullPointerException(const char* message) : Exception(message)  { }
    NullPointerException(char* file, int line) : Exception(file, line) { }
    NullPointerException(const char* message, const char* file, int line) : Exception(message, file, line) { }
    NullPointerException(const NullPointerException& e) :  Exception(e) { }
    NullPointerException& operator=(const NullPointerException& e)
    {
        Exception::operator=(e);
        return *this;
    }
};


class IndexOutOfBoundsException : public Exception
{
    IndexOutOfBoundsException(const char* message) : Exception(message)  { }
    IndexOutOfBoundsException(char* file, int line) : Exception(file, line) { }
    IndexOutOfBoundsException(const char* message, const char* file, int line) : Exception(message, file, line) { }
    IndexOutOfBoundsException(const IndexOutOfBoundsException& e) :  Exception(e) { }
    IndexOutOfBoundsException& operator=(const IndexOutOfBoundsException& e)
    {
        Exception::operator=(e);
        return *this;
    }
};

class NoEnoughMemoryException : public Exception
{
    NoEnoughMemoryException(const char* message) : Exception(message)  { }
    NoEnoughMemoryException(char* file, int line) : Exception(file, line) { }
    NoEnoughMemoryException(const char* message, const char* file, int line) : Exception(message, file, line) { }
    NoEnoughMemoryException(const NoEnoughMemoryException& e) :  Exception(e) { }
    NoEnoughMemoryException& operator=(const NoEnoughMemoryException& e)
    {
        Exception::operator=(e);
        return *this;
    }
};

class InvalidParameterException : public Exception
{
    InvalidParameterException(const char* message) : Exception(message)  { }
    InvalidParameterException(char* file, int line) : Exception(file, line) { }
    InvalidParameterException(const char* message, const char* file, int line) : Exception(message, file, line) { }
    InvalidParameterException(const InvalidParameterException& e) :  Exception(e) { }
    InvalidParameterException& operator=(const InvalidParameterException& e)
    {
        Exception::operator=(e);
        return *this;
    }
};

}
#endif // !__EXCEPTION_H__