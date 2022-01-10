#ifndef __BTREE_H__
#define __BTREE_H__

#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"

namespace DTLib
{

 enum BTNodePos
{
    ANY,
    LEFT,
    RIGHT
};
template < typename T >
class BTree : public Tree<T>
{
public:
    bool insert(BTreeNode<T>* node)
    {
        return insert(node, ANY);
    }

    bool insert(BTreeNode<T>* node, BTNodePos pos)
    {
        return insert(node, pos);
    }

    bool insert(const T& value, BTreeNode<T>* parent) 
    {
        return insert(vlaue, parent, ANY);
    }

    bool insert(const T& value, BTreeNode<T>* parent, BTNodePos pos) 
    {
        bool ret = NULL;

        BTreeNode<T>* node = BTreeNode<T>::NewNode();

        if ( node == NULL )
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new node ....");
        }
        else
        {
            node->value = value;
            node->parent = parent;

            ret = insert(node, pos);

            if ( !ret )
            {
                delete node;
            }
        }
    }

    SharedPointer< Tree<T> > remove(const T& value) 
    {

    }

    SharedPointer< Tree<T> > remove(BTreeNode<T>* node) 
    {

    }

    BTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    BTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(), dynamic_cast<BTreeNode<T>*>(node));
    }

    BTreeNode<T>* root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
    }

    int degree() const 
    {

    }

    int count() const 
    {

    }

    int height() const 
    {

    }

    void clear() 
    {
        this->m_root = NULL;
    }

    ~BTree()
    {
        clear();
    }

protected:
    virtual BTreeNode<T>* find(BTreeNode<T>* node, const T& value) const
    {
        BTreeNode<T>* ret = NULL;

        if ( node != NULL )
        {
            if ( node->value == value)
            {
                ret = node;
            }
            else
            {
                if ( ret == NULL )
                {
                    ret = find(node->left, value);
                }
                
                if ( ret == NULL )
                {
                    ret = find(node->right, value);
                }
            }
        }

        return ret;
    }

    virtual BTreeNode<T>* find(BTreeNode<T>* root, BTreeNode<T>* node) const
    {
        BTreeNode<T>* ret = NULL;

        if ( root != NULL )
        {
            if ( root == node )
            {
                ret = root;
            }
            else
            {
                if ( ret == NULL )
                {
                    ret = find(root->left, node);
                }

                if ( ret == NULL )
                {
                    ret = find(root->right, node);
                }

            }
        }

        return ret;
    }

    virtual bool insert(TreeNode<T>* node, BTNodePos pos)
    {
        bool ret = true;

        if ( node == NULL )
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node can not be NULL"));
        }
        else
        {
            if ( this->m_root == NULL )
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                BTreeNode<T>* np = find(node->parent);

                if ( np != NULL )
                {
                    ret = insert(dynamic_cast<BTreeNode<T>*>(node), np, pos);
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "Invalid parent tree node ....");
                }
            }
        }
        return ret;
    }
    virtual insert(BTreeNode<T>* n, BTreeNode<T>* np, BTNodePos pos)
    {
        bool ret = true;

        if ( pos == ANY )
        {
            if ( np->left == NULL )
            {
                np->left = n;
            }
            else if ( np->right == NULL )
            {
                np->right = n;
            }
            else
            {
                ret = false;
            }
        }
        else if ( pos == LEFT )
        {
            if ( np->left == NULL )
            {
                np->left = n;
            }
            else
            {
                ret = false;
            }
        }
        else if ( pos == RIGHT )
        {
            if ( np->right == NULL )
            {
                np->right = n;
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = false;
        }
    }   
};


}

#endif // !__BTREE_H__
