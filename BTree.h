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
        Tree<T>* ret = NULL;
        BTreeNode<T>* node = find(value);

         if ( node == NULL )
        {
            THROW_EXCEPTION(InvalidParameterException, "Can not find the tree node via value ....");
        }
        else
        {
            remove(node ret);

            m_queue.clear();
        }
        
        return ret;
    }

    SharedPointer< Tree<T> > remove(BTreeNode<T>* node) 
    {
        Tree<T>* ret = NULL;

        node = find(node);

        if ( node == NULL )
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid ....");
        }
        else
        {
            remove(dynamic_cast<BTreeNode<T>*>(node), ret);
            
            m_queue.clear();
        }

        return ret;
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
        return degree(root());
    }

    int count() const 
    {
        return (node != NULL) ? (count(node->left) + count(node->right) + 1) : 0;
    }

    int height() const 
    {
        return height(root());
    }

    void clear() 
    {
        free(root());
        m_queue = NULL;
        this->m_root = NULL;
    }

    bool begin()
    {
        bool ret = (root() != NULL);

        if ( ret )
        {
            m_queue.clear();
            m_queue.add(root());

        }

        return ret;
    }

    bool end()
    {
        return (m_queue.length() == 0);
    }

    bool next()
    {
        bool ret = (m_queue.m_length() > 0);

        if ( ret )
        {
            GTreeNode<T>* node = m_queue.front();

            m_queue.remove();

            if ( node->left )
            {
                m_queue.add(node->left);
            }

            if ( node->right )
            {
                m_queue.add(node->right);
            }
        }

        return ret;
    }   

    T current()
    {
        if ( !end() )
        {
            return m_queue.front()->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ....");
        }
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
    
    virtual void remove(BTreeNode<T>* node, BTree<T>*& ret)
    {
        ret = new BTree<T>();

        if ( ret == NULL )
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree ...");
        }
        else
        {
            if ( root() == node )
            {
                this->root = NULL;
            }
            else
            {
                BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent());

                if ( parent->left == node )
                {
                    parent->left = NULL;
                }
                else if ( parent->right == node )
                {
                    parent->right = NULL;
                }

                node->parent = NULL;
            }

            ret->m_root = node;
        }
    }

    virtual void free(BTreeNode<T>* node)
    {
        if ( node != NULL )
        {
            free(node->left);
            free(node->right);

            if ( node->flag() )
            {
                delete node;
            }

        }
    }

    virtual int count(BTreeNode<T>* node) const
    {
        int ret = 0;

        if ( node != NULL )
        {
            ret = count(node->left) + count(node->right) + 1;
        }

        return ret;
    }

    virtual int height(BTreeNode<T>* node) const 
    {
        int ret = 0;

        if ( node != NULL )
        {
            int lh = heiget(node->left);
            int rh = height(node->right);

            ret = ((lh > rh) ? lh : rh) + 1;
        }

        return ret;
    }

    virtual int degree(BTreeNode<T>* node) const
    {
        int ret = 0;

        if ( node != NULL )
        {
            // int dl = degree(node->left);
            // int dr = degree(node->right);

            // ret = (!!node->left + !!node->right);

            // if ( ret < dl )
            // {
            //     ret = dl;
            // }

            // if ( ret < dr )
            // {
            //     ret = dr;
            // }

            // ret = (!!node->left + !!node->right);

            // if ( ret  < 2 )
            // {
            //     int dl = degree(node->left);               

            //     if ( ret < dl )
            //     {
            //         ret = dl;
            //     }
            // }

            // if ( ret < 2 )
            // {
            //     int dr = degree(node->right);
                
            //     if ( ret < dr )
            //     {
            //         ret = dr;
            //     }
            // }
            ret = (!!node->left + !!node->right);
            BTreeNode<T>* child[] = { node->left, node->right };

            for (int i = 0; ( i < 2 ) && ( ret < 2 ) ; i++)
            {
                int d = degree(child[i]);

                if ( ret < d )
                {
                    ret = d;
                }
            }

        }

        return ret;
    }

protected:
    LinkQueue<BTreeNode<T>*> m_queue;
};


}

#endif // !__BTREE_H__
