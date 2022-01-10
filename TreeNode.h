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
        m_flag = false;
    }

    bool flag()
    {
        return m_flag;
    }


    virtual ~TreeNode() = 0;

protected:
    TreeNode(const TreeNode<T>&);
    TreeNode<T>& operator = (const TreeNode<T>&);
    void* operator new(unsigned int size) throw()
    {
        return Object::operator new(size);
    }

    bool m_flag;

};

template < typename T >
TreeNode<T>::~TreeNode()
{

}

}

#endif // !__TREENODE_H__
