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
        GTreeNode<T>* node = GTreeNode<T>::NewNode();

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
        GTree<T>* ret = NULL;
        GTreeNode<T>* node = find(value);

        if ( node == NULL )
        {
            THROW_EXCEPTION(InvalidParameterException, "Can not find the node via paramter value ...");
        }
        else
        {
            remove(node, ret);
        }

        return ret;
    }

    virtual SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        GTree<T>* ret = NULL;
        node = find(node);

        if ( node == NULL )
        {
            THROW_EXCEPTION(InvalidParameterException, "Can not find the node via node ...");
        }
        else
        {
            remove(dynamic_cast<GTreeNode<T>*>node, ret);
        }

        return ret;
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
        free(root());
        delete m_root;
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

    void free(GTreeNode<T>* node)
    {
        if ( node == NULL )
        {
            return ;
        } 

        for (node->child.move(0); !node->child.end(); node->child.next())
        {
            free(node->child.current());
        }

        if ( node->flag() )
        {
            delete node; // 需要判断是否是堆里面的空间
        }
    }

    void remove(GTreeNode<T>* node, GTreeNode<T>*& ret)
    {
        ret = new GTree<T>();

        if ( ret == NULL )
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree");
        }
        else
        {
            if ( root() == node )
            {
                this->m_root = NULL;
            }
            else
            {
                LinkList<GTreeNode<T>*>& child = dynamic_cast<GTreeNode<T>*>(node->parent)->child;
                
                child.remove(child.find(node));

                node->parent = NULL;
            }

            ret->m_root = node;
        }
    }

};

}

#endif // !__GTREE_H__
