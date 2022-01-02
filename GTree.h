#ifndef __GTREE_H__
#define __GTREE_H__

#include "Tree.h"
#include "GTreeNode.h"

namespace DSLib
{

template < typename T >
class GTree : public Tree<T>
{
public:
    virtual bool insert(TreeNode<T>* node)
    {
        bool ret = true;

        if ( node != NULL )
        {
            if ( this->m_root == NULL )
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                GTreeNode<T>* np = find(node->parent);

                if ( np != NULL )
                {
                    GTreeNode<T>* n = dynamic_cast<GTreeNode<T>*>(node);

                    if ( np->child.find(n) < 0 )
                    {
                        np->child.insert(n);
                    }
                }
                else
                {
                    THROW_EXCEPTION(InvalidOperationException, "Invalid parent tree node ....");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Param node cannot be NULL...");
        }
    }

    virtual bool insert(const T& value, TreeNode<T>* parent)
    {
        bool ret = true;
        GTreeNode<T>* node = new GTreeNode<T>();

        if ( node != NULL )
        {
            node->value = value;
            node->parent = parent;
            
            insert(node);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree node ....");
        }
    }

    virtual SharedPointer< Tree<T> > remove(const T& value)
    {

    }

    virtual SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {

    }

 

    virtual GTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    virtual GTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(),  dynamic_cast<GTreeNode<T>*>(node));
    }

    virtual GTreeNode<T>* root() const
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }

    virtual int degree() const
    {
        return 0;
    }

    virtual int count() const
    {

    }

    virtual int height() const
    {

    }

    virtual void clear() 
    {
        this->root = NULL;
    }

    ~GTreeNode()
    {

    }

protected:
    GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const
    {   
        GTreeNode<T>* ret = NULL;

        if ( node != NULL )
        {
            if ( node->value == value )
            {
                return node;
            }
            else
            {
                for (node->child.move(0), !node->child.end() && (ret == NULL); node->child.next())
                {
                    ret = find(node->child.current(), value);
                }
            }
        }

        return ret;

    }

    GTreeNode<T>* find(GTreeNode<T>* node, GTreeNode<T>* obj) 
    {
        GTreeNode<T>* ret = NULL;

        if ( node != NULL )
        {
            if ( node == obj )
            {
                return node;
            }
            else
            {
                for (node->child.move(0), !node->child.end() && (ret == NULL); node->child.next())
                {
                    ret = find(node->child.current(), obj);
                }
            }
        }

        return ret;
    }


};

}

#endif // !__GTREE_H__
