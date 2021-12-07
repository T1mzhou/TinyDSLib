#ifndef __STATICLINKLIST_H__
#define __STATICLINKLIST_H__

#include "LinkList.h"

namespace DSLib
{

template < typename  T, int N >
class StaticLinkList : public LinkList<T>
{
public:
    StaticLinkList()
    {
        for (int i = 0; i < N; i++)
        {
            m_used[i] = 0;
        }
    }

    int capacity()
    {
        return N;
    }    

protected:
    typedef typename LinkList<T>::Node Node;

    struct SNode : public Node
    {
        void* operator new(unsigned int size, void* loc)
        {
            (void) size; // 不使用    
            return loc;  // 返回调用构造函数的地址
        }
    };

    unsigned char m_space[sizeof(SNode) * N];
    int m_used[N];

    Node* create()
    {
        SNode* ret = NULL;

        for (int i = 0; i < N; i++)
        {
            if ( !m_used[i] )
            {
                ret = reinterpret_cast<SNode*>(m_space) + i;  // 只是分配了空间，需要在分配的空间上调用构造函数
                ret = new(ret)SNode();                        // 调用构造函数
                m_used[i] = 1;
                break;
            }
        }

        return ret;
    }

    Node* destroy(Node* pn)
    {
        SNode* space = reinterpret_cast<SNode*>(m_space);
        SNode* psn = dynamic_cast<SNode*>(pn);

        for (int i = 0; i < N; i++)
        {
            if ( pn == (space + i) )
            {
                m_used[i] = 0;
                psn->~SNode();
                break;          // impove efficiency
            }
        }
    }
};

}

#endif // !__STATICLINKLIST_H__