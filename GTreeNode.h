#ifndef __GTREENODE_H__
#define __GTREENODE_H__

#include "TreeNode.h"
#include "LinkList.h"

namespace DSLib
{

template< typename T >
class GTreeNode : public TreeNode<T>
{
public:
    GTreeNode()
    {
        m_flag = false;
    }

    bool flag()
    {
        return m_flag;
    }
    
    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T>* ret = new GTreeNode<T>();

        if ( ret != NULL )
        {
            ret->m_flag = true;
        }
    }

public:
    LinkList<GTreeNode<T>*> child;
protected:
    void* operator new(unsigned int size) throw()
    {
        return Object::operator new(size);
    }

    bool m_flag;
};

}

#endif // !__GTREENODE_H__