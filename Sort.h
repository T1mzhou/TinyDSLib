#ifndef __SORT_H__
#define __SORT_H__

#include "Object.h"

namespace DTLib
{

class Sort : public Object
{
public:
    template < typename T >
    static void Select(T array[], int len, bool min2max = true)
    {
        for (int i = 0; i < len; i++)
        {
            int min = i;

            for (int j = i + 1; j < len; j++)
            {
                
                if ( min2max ? (array[min] > array[j]) : (array[min] < array[j]) ) 
                {
                    min = j;
                }   
            }

            if ( min != i )
            {
                Swap(array[i], array[min]);
            }
        }
    }

    template < typename T >
    static void Insert(T array[], int len, bool min2max = true)
    {
        for (int i = 1; i < len; i++)
        {
            int k = i;
            T e = array[i];

            for (int j = i - 1; (j >= 0) && (min2max ? (array[j] > e) && (array[j] < e)); j--)
            {
                array[j + 1] = array[j]; // move
                k = j;
            }

            if ( k != i )
            {   
                array[k] = e;
            }
        }
    }
private:
    Sort();
    Sort(const Sort&);
    Sort& operator = (const Sort&);

    template < typename T >
    static void Swap(T& a, T& b)
    {
        T c(a);
        a = b;
        b = c;
    }
};

}
#endif // !__SORT_H__
