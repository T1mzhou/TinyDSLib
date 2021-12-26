#ifndef __STRING_H__
#define __STRING_H__

#include "Object.h"
#include "Exception.h"

namespace DSLib
{

template < typename T >
class String : public Object
{
public:
    String();
    String(char c);
    String(const char* s);
    String(const String& s);
    
    int length();
    const char* str() const;

    bool operator == (const string& s) const;
    bool operator == (const char* s) const;
    bool operator != (const string& s) const;
    bool operator != (const char* s) const;
    bool operator > (const string& s) const;
    bool operator > (const char* s) const;
    bool operator < (const string& s) const;
    bool operator < (const char* s) const;
    bool operator >= (const string& s) const;
    bool operator >= (const char* s) const;
    bool operator <= (const string& s) const;
    bool operator <= (const char* s) const;

    String operator + (const String& s) const;
    String operator + (const char* s) const;
    String& operator += (const String& s);
    String& operator += (const char* s);
    String& operator = (const String& s);
    String& operator = (const char* s);
    String& opearator = (char c);

    ~String();

protected:
    void init(const char* s);
protected:
    char* m_str;
    int m_length;
};

}
#endif // !__STRING_H__