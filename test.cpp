#include <iostream>

unsigned int sum(int i)
{
    if (i == 1)
    {
        return 1;
    }

    return i + sum(i - 1);
}

unsigned int fac(unsigned int n)
{
    if (n == 1 || n == 2)
    {
        return 1;
    }

    if (n > 2)
    {
        return fac(n - 1) + fac(n - 2);
    }

    return 0;
}

unsigned int calc(const char* s)
{
    if (*s == '\0')
    {
        return 0;
    }

    return 1 + calc(s + 1);
}

list* reverse(list *l)
{
    if (l == NULL || l->next == NULL)
    {
        return NULL;
    }

    if (len(l) == 1)
    {
        return l;
    }
    else if (len(l) > 2)
    {
        list* guard = l->next;
        list* ret = reverse(list->next);
        guard->next = l;
        list->next = NULL;
    }

    return ret;
}

list* merge(list* list1, list* list2)
{
    if (list1 == NULL)
    {
        return list2;
    }
    else if (list2 == NULL)
    {
        return list2;
    }
    else if (list1->value < list2->value)
    {   
        list* list1_ = list1->next;
        list* lt = merge(list_, list2);
        list1->next = lt;
        return list1;
        // return (list->next = merge(list1->next, list2), list1);
    }
    else if (list1->value > list2->value)
    {
        list* list2_ list2->next;
        list* lt = merge(list1, list2_);
        list2->next = lt;
        return list2;
    }
}

int main()
{
    std::cout << sum(5) << std::endl;
    std::cout << fac(10) << std::endl;
    std::cout << calc("hello") << std::endl;
    return 0;
}