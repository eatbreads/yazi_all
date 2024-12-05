#pragma once

#include <ttl/bs_tree.h>
#include <ttl/rb_tree_node.h>

namespace ttl
{
    template <typename T>
    class RBTree : public BSTree<T>
    {
        typedef RBTreeNode<T> Node;
    public:
        RBTree();
        virtual ~RBTree();

        virtual void insert(const T & key);           // 插入
        virtual void remove(const T & key);           // 删除 

        virtual bool add(const T & key);              // 非递归插入
        virtual bool del(const T & key);              // 非递归删除

    protected:
        virtual TreeNode<T> * create_node(const T & key);
        virtual void delete_node(TreeNode<T> * node);
        virtual TreeNode<T> * insert(TreeNode<T> * root, const T & key);    // 递归插入
        virtual TreeNode<T> * remove(TreeNode<T> * root, const T & key);    // 递归删除

        TreeNode<T> * insert_fix(TreeNode<T> * root);
        TreeNode<T> * remove_fix(TreeNode<T> * root);
        TreeNode<T> * del_fix(TreeNode<T> * node);

        bool is_color(TreeNode<T> * node, char color); 
        void set_color(TreeNode<T> * node, char color);

    private://当出现了需要旋转的情况的时候,就会在对应位置打上标记
        bool m_l = false;           //需要左旋
        bool m_r = false;           //需要右旋
        bool m_lr = false;          //先左旋后右旋
        bool m_rl = false;          //先右旋后左旋
    };

#include <ttl/rb_tree.inl>

}
