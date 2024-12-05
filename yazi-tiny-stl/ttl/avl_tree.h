#pragma once

#include <ttl/bs_tree.h>
#include <ttl/avl_tree_node.h>

template <typename T>
T max(const T & a, const T & b)
{
    return a > b ? a : b;
}

namespace ttl
{
    template <typename T>
    class AVLTree : public BSTree<T>
    {
        typedef AVLTreeNode<T> Node;
    public:
        AVLTree();
        virtual ~AVLTree();

        virtual void insert(const T & key);           // 插入
        virtual void remove(const T & key);           // 删除

        virtual bool add(const T & key);              // 非递归插入
        virtual bool del(const T & key);              // 非递归删除

    protected:
        virtual TreeNode<T> * create_node(const T & key);
        virtual void delete_node(TreeNode<T> * node);
        virtual TreeNode<T> * insert(TreeNode<T> * root, const T & key);    // 递归插入
        virtual TreeNode<T> * remove(TreeNode<T> * root, const T & key);    // 递归删除
        virtual TreeNode<T> * left_rotate(TreeNode<T> * node);              // 左旋转
        virtual TreeNode<T> * right_rotate(TreeNode<T> * node);             // 右旋转

        TreeNode<T> * insert_fix(TreeNode<T> * root);
        TreeNode<T> * remove_fix(TreeNode<T> * root);

        int height(TreeNode<T> * node) const; 
        int get_balance_factor(TreeNode<T> * node);
        TreeNode<T> * rebalance(TreeNode<T> * root);
    };

#include <ttl/avl_tree.inl> 

}
