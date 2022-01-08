#ifndef __GTREE_H__
#define __GTREE_H__

#include "Tree.h"
#include "GTreeNode.h"
#include "LinkQueue.h"
#include "Exception.h"

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

            m_queue.clear();
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
        return degree(root());
    }

    virtual int count() const
    {
        return count(root());
    }

    virtual int height() const
    {
        return height(root());
    }

    virtual void clear() 
    {
        free(root());
        
        this->m_root = NULL;

        m_queue.clear();
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

            for (node->child.move(0); !node->child.end(); node->child.next())
            {
                m_queue.add(node->child.current());
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


    ~GTreeNode()
    {

    }

protected:
    LinkList<GTreeNode<T>*> m_queue;

protected:
    GTree(const GTree<T>& );
    GTree<T>& operator = (const GTree<T>& );

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

    int count(GTreeNode<T>* node)
    {
        int ret = 0;

        if ( node != NULL )
        {
            ret = 1;

            for (node->child.move(0); !node->child.end(); node->child.next())
            {
                ret += count(node->child.current());
            }
        }

        return ret;
    }

    int height(GTreeNode<T>* node)
    {
        int ret = 0;

        if ( node != NULL )
        {
            ret = 1;

            for (node->child.move(0); !node->child.end(); node->child.next())
            {
                int h = height(node->child.current());

                if ( ret < h )
                {
                    return h;
                }
            }

            ret = ret + 1;
        }

        return ret;
    }

    int degree(GTreeNode<T>* node) const
    {
        int ret = 0;

        if ( node != NULL )
        {
            ret = node->child.length();
            
            for (node->child.move(0); !node->child.end(); node->child.next())
            {
                int d = degree(node->child.current());

                if ( ret < d )
                {
                    ret = d;
                }
            }
        }

        return ret;
    }
};

}

#endif // !__GTREE_H__