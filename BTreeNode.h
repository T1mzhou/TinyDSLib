#ifndef __BTREENODE_H__
#define __BTREENODE_H__

#include "TreeNode.h"

namespace DSLib
{

template < typename T >
class BTreeNode : public TreeNode
{
public:
    BTreeNode()
    {
        left = NULL;
        right = NULL;
    }

    static BTreeNode* NewNode();
    {
        BTreeNode<T>* ret = new BTreeNode<T>();

        if ( ret != NULL )
        {
            ret->m_flag = true;
        }

        return ret;
    }

public:
    BTreeNode<T>* left;
    BTreeNode<T>* right;
};

}

#endif // !__BTREENODE_H__
