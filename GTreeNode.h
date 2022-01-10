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
 
};

}

#endif // !__GTREENODE_H__