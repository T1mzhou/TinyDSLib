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

    static int* make_pmt(const char* p);
    static int kmp(const char* s, const char* p);

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

    String operator - (const String& s);
    String operator - (const char* s);
    String& operator -= (const String& s);
    String& operator -= (const char* s);

    char& operator [](size_t i);
    char opearor [](size_t i) const;
    bool startWith(const String& s);
    bool startWith(const char* s);
    bool endOf(const String& s);
    bool endOf(const char* s);
    String& insert(int i, const String& s);
    String& insert(int i, const char* s);
    String& trim();
    int indexOf(const char* s) const;
    int indexof(const string& s) const;
    String& remove(int i, int len);
    String& remove(const char* s);
    String& remove(const String& s);
    String& replace(const char* t, const char* s);
    String& replace(const String& t, const char* s);
    String& replace(const char* t, const String& s);
    String& replace(cosnt String& t, const String& s);
    String sub(int i, int len) const;

    ~String();

protected:
    void init(const char* s);
    bool equal(const char* l, const char* r, int len) const;
protected:
    char* m_str;
    int m_length;
};

}
#endif // !__STRING_H__