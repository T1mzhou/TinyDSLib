#ifndef __BTREE_H__
#define __BTREE_H__

#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"

namespace DTLib
{

template < typename T >
class BTree : public Tree<T>
{
public:
     bool insert(BTreeNode<T>* node)
     {

     }

     bool insert(const T& value, BTreeNode<T>* parent) 
     {

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
        return find(root(), node);
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
};


}

#endif // !__BTREE_H__
