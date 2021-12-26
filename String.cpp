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
    
    return (*this = s);
}


char& String::operator [](size_t i)
{
    if ( (0 <= i) && (i < m_length) )
    {
        return m_str[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Paramter i is invalid ....");
    }
    return (*this[i]);
}
    
char String::opearor [](size_t i) const
{
    return (const_cast<String&>(*this))[i]);
}

bool equal(const char* l, const char* r, int len) const
{
    bool ret = true;

    for (int i = 0; i < len && ret; i++)
    {
       ret = ret && (l[i] == r[i]);
    }

    return ret;
}


bool String::startWith(const String& s)
{
    return startWith(s.m_str)
}

bool String::startWith(const char* s)
{
    bool ret = (s != NULL);

    if ( ret )
    {
        int len = strlen(s);

        ret = (len < m_length) && equal(m_str, s, len);

    }
   
    return true;
}
    
bool String::endOf(const String& s)
{
    return endOf(s.m_str);
}

bool String::endOf(const char* s)
{
    bool ret = (s != NULL);

    if ( ret )
    {
        int len = strlen(s);
        char* str = m_str + (m_length - len);
        
        ret = (len < m_length) && equal(str, s, len);
    }
}


 String& String::insert(int i, const String& s)
 {
     return insert(i, s.m_str);
 }

    
String& String::insert(int i, const char* s)
{
    if ( (0 <= i) && (i <= m_length) )
    {
        if ( (s != NULL) && (s[0] != '\0') )
        {
            int len = strlen(s);
            char* str = reinterpret_cast<char*>malloc(m_length + len + 1);

            if ( str != NULL )
            {
                strncpy(str, m_str, i);
                strncpy(str + i, s, len);
                strncpy(str + i + len, m_str + i， m_length - i)；

                str[m_length + len ] = '\0';

                free(m_str);
                m_str = str;
                m_length = m_length + len;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert string value .... ");
            }
        }
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ... ");
    }

    return *this;
}

String& String::trim()
{
    int b = 0;
    int e = m_length - 1;

    while ( m_str[b] == ' ') b++;
    while ( m_str[e] == ' ') e--;

    if ( b == 0 )
    {
        m_str[e + 1] = '\0';
        m_lenght = e + 1;
    }
    else
    {
        for (int i = 0, j = b; j <= e; i++, j++)
        {
            m_str[i] = m_str[j];
        }

        m_str[e - b + 1] = '\0';
        m_length = e - b + 1;
    }

    return *this;
}

String::~String()
{
    if ( m_str )
    {
        free(m_str)
    }
}