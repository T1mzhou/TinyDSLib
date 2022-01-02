#ifndef __TREENODE_H__
#define __TREENODE_H__

#include "Object.h"

namespace DSLib
{

template < typename T >
class TreeNode : public Object
{
public:
    T value;
    TreeNode<T>* parent;

    TreeNode()
    {
        parent = NULL;
    }

    virtual ~TreeNode() = 0;
};

template < typename T >
TreeNode<T>::~TreeNode()
{

}

}

#endif // !__TREENODE_H__
