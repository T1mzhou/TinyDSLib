#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

namespace DSLib
{
class Exception
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
}
#endif // !__EXCEPTION_H__