#include "DSString.h"
#include <cstring>
#include <cstdlib>

using namespace std;

namespace DSLib
{
    
void String::init(const char* s)
{
    m_str = strdup(s);

    if ( m_str )
    {
        m_length = strlen(m_str);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to create String Object ....");
    }
}

String::String()
{
    init("");
}

String::String(const char* s)
{
    init(s ? s : "");   //  avoid null ptr
}

String::String(const String& s)
{
    init(s.m_str);
}

String::String(char c)
{
    char s[] = {c, '\0'};
    
    init(s);
}

int String::length() const
{
    return m_length;
}

const char* String::str() const
{
    return m_str;
}


 bool String::operator == (const string& s) const
 {
     return (strcmp(m_str, s.m_str));
 }

bool String::operator == (const char* s) const
 {
     return (strcmp(m_str, s ? s : ""));
 }


bool String::operator !=(const string& s) const
 {
    return !(*this == s);
 }


 bool String::operator != (const char* s) const
 {
     return !(*this == s);
 }

bool String::operator > (const string& s) const
 {
    return (strcmp(m_str, s.m_str) > 0);
 }

 bool String::operator > (const char* s) const
 {
     return (strcmp(m_str, s ? s : "") > 0);
 }

 bool String::operator < (const string& s) const
 {
    return (strcmp(m_str, s.m_str) < 0);
 }

 bool String::operator < (const char* s) const
 {
     return (strcmp(m_str, s ? s : "") < 0);
 }

 bool String::operator >= (const string& s) const
 {
    return (strcmp(m_str, s.m_str) >= 0);
 }

 bool String::operator >= (const char* s) const
 {
     return (strcmp(m_str, s ? s : "") >= 0);
 }

 bool String::operator <= (const string& s) const
 {
    return (strcmp(m_str, s.m_str) <= 0);
 }

 bool String::operator <= (const char* s) const
 {
     return (strcmp(m_str, s ? s : "") <= 0);
 }


String String::operator + (const String& s) const
{
    return (*this + s.m_str);
}

String String::operator + (const char* s) const
{
    String ret;
    int len = m_length + strlen(s ? s : "");
    char* str = reinterpret_cast<char*>malloc(len + 1);

    if ( str )
    {
        stcpy(str, m_str);
        strcat(str, s ? s : "");
        
        free(ret.m_str);
        
        ret.m_str = str;
        ret.length = len;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memeroy to add String values ....");
    }

    return ret;
}

String& String::operator += (const String& s)
{
    return (*this = *this + s);
}
    
String& String::operator += (const char* s)
{
    return (*this = *this + s);
}

String& String::operator = (const String& s)
{
    return (*this = s.m_str);
}

String& String::operator = (const char* s)
{
    if ( m_str != s )
    {
        char* str = strdup(s ? s : "");

        if ( str )
        {
            free(m_str);

            m_str = str;
            m_length = strlen(m_str);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to assign new String value ....");
        }
    }
}
 
String& String::opearator = (char c)
{
    char s[] = {c, "\0"};
    
    return (*this = s};
}

String::~String()
{
    if ( m_str )
    {
        free(m_str)
    }
}