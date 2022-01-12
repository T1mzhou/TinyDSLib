#ifndef __BTREE_H__
#define __BTREE_H__

#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"
#include "DynamicArray.h"

namespace DTLib
{

 enum BTNodePos
{
    ANY,
    LEFT,
    RIGHT
};

enum BTTraversal
{
    PreOrder,
    InOrder,
    PostOrder,
    LevelOrder
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

    SharedPointer< Array<T> > traversal(BTTraversal order)
    {
        DynamicArray<T>* ret = NULL;
        LinkQueue<BTreeNode<T>*> queue;

        traversal(order, queue);

        ret = new DynamicArray<T>(queue.length());

        if ( ret != NULL )
        {
            for (int i = 0; i < ret->length(); i++)
            {
                ret->set(i, queue.front()->value);
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memroy to create return array ....");

        }

        return ret;
    }

    SharedPointer<BTree<T> > clone() const
    {
        BTree<T>* ret = new BTree<T>();

        if ( ret != NULL )
        {
            ret->m_root = clone(root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memroy to create return btree ....");

        }
    }

    bool operator == (const BTree<T>& btree)
    {
        return equal(root(), btree.root());
    }

    bool operator != (const BTree<T>& btree)
    {
        return !(*this == btree);
    }

    SharePointer< BTree<T> > add(const BTree<T>& btree) const
    {
        BTree<T>* ret = new BTree<T>();

        if ( ret  != NULL )
        {
            ret->m_root = add(root(), btree.root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memroy to create new tree ....");
        }

        return ret;
    }

    BTreeNode<T>* thread(BTTraversal order)
    {
        BTreeNode<T>* ret = NULL;
        LinkQueue<BTreeNode<T>*> queue;

        traversal(order, queue);

        connect(queue);

        this->root = NULL;
        m_queue.clear();

        return ret;
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
            if ( node->value == value )
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

    void preOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if ( node != NULL )
        {
            queue.add(node);
            preOrderTraversal(node->left, queue);
            preOrderTraversal(node->right, queue);
        }
    }

    void inOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if ( node != NULL )
        {
            inOrderTraversal(node->left, queue);
            queue.add(node);
            inOrderTraversal(node->right, queue);
        }
    }

    void postOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if ( node != NULL )
        {
            postOrderTraversal(node->left, queue);
            postOrderTraversal(node->right, queue);
            queue.add(node);
        }
    }

    void levelOrderTraversal(BTreeNNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if ( node != NULL )
        {
            LinkQueue<BTreeNode<T>*> tmp;

            tmp.add(root());

            while ( tmp.length() > 0 )
            {
                BTreeNode<T>* n = tmp.front();

                if ( n->left != NULL )
                {
                    tmp.add(n->left);
                }

                if ( n->right != NULL )
                {
                    tmp.add(n->right);
                }

                tmp.remove();
                queue.add(n);

            }
        }
    }

    BTreeNode<T>* clone(BTreeNode<T>* node) const
    {
        BTreeNode<T>* ret = NULL;

        if ( node != NULL )
        {
            ret = BTreeNode<T>::NewNode();

            if ( ret != NULL )
            {
                ret->value = node->value;

                ret->left = clone(node->left);
                ret->right = clone(node->right);

                if ( ret->left != NULL )
                {
                    ret->left->parent = ret;
                }
                
                if ( ret->right != NULL )
                {
                    ret->right->parent = ret;
                }

            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new node ...");
            }
        }

        return ret;
    }

    bool equal(BTreeNode<T>* lh, BTreeNode<T>* rh)
    {
        if ( lh == rh )
        {
            return true;
        }
        else if ( (lh != NULL) && (rh != NULL) )
        {
            return (lh->value == rh->value) && equal(lh->left, rh->left) && equal(lh->right, rh->right);
        }
        else
        {
            return false;
        }
    }

    BTreeNode<T>* add(BTreeNode<T>* lh, BTreeNode<T>* rh) const
    {
        BTreeNode<T> ret = NULL;

        if ( (lh == NULL) && (rh != NULL ) )
        {
            ret = clone(rh);
        }
        else if ( (lh != NULL) && (rh == NULL))
        {
            ret = cloen(lh);
        }
        else if ( (lh != NULL) && (rh != NULL))
        {
            ret = BTreeNode<T>::NewNode();

            if ( ret != NULL )
            {
                ret->value = lh->value + rh->value;

                ret->left = add(lh->left, rh->left);
                ret->right = add(lh->right, rh->right);

                if ( ret->left != NULL )
                {
                    ret->left->parent = ret;
                }

                if ( ret->right != NULL )
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new node ...");
            }
        }
    }

    void traversal(BTTraversal order, LinkQueue<BTreeNode<T>*> queue)
    {
        if ( node != NULL )
        {
            switch (order)
            {
            case PreOrder:
                preOrderTraversal(root(), queue);
                break;
            case InOrder:
                inOrderTraversal(root(), queue);
                break;
            case PostOrder:
                postOrderTraversal(root(), queue);
                break;
            case LevelOrder:
                levelOrderTraversal(root(), queue);
                break;
            default:
                THROW_EXCEPTION(InvalidParameterException, "Parameter order is invalid ...");
                break;
            }
        }
    }

    BTreeNode<T>* connect(LinkQueue<BTreeNode<T>*>& queue)
    {
        BTreeNode<T>* ret = NULL;

        if ( queue.length() > 0 )
        {
            ret = queue.front();

            BTreeNode<T>* slider = queue.front();

            queue.remove();

            slider->left = NULL;

            while ( queue.length() > 0 )
            {
                slider->right = queue.front();
                queue.front()->left = slider;
                slider = queue.front();
                queue.remove();
            }

            slider->right = NULL;
        }


        return ret;      
    }


    

protected:
    LinkQueue<BTreeNode<T>*> m_queue;
};


}

#endif // !__BTREE_H__
