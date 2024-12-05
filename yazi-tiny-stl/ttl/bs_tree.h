#pragma once

#include <iostream>
#include <ttl/tree.h>
#include <ttl/bs_tree_node.h>

namespace ttl
{
    template <typename T>
    class BSTree : public Tree<T>
    {
        typedef BSTreeNode<T> Node;
    public:
        BSTree();
        virtual ~BSTree(); 

        virtual void insert(const T & key);             // 插入
        virtual void remove(const T & key);             // 删除

        virtual bool add(const T & key);                // 非递归插入
        virtual bool del(const T & key);                // 非递归删除

    protected:
        virtual TreeNode<T> * create_node(const T & key);
        virtual void delete_node(TreeNode<T> * node);

        // 递归操作
        virtual TreeNode<T> * insert(TreeNode<T> * root, const T & key);    // 递归插入
        virtual TreeNode<T> * remove(TreeNode<T> * root, const T & key);    // 递归删除

        virtual TreeNode<T> * left_rotate(TreeNode<T> * node);              // 左旋转
        virtual TreeNode<T> * right_rotate(TreeNode<T> * node);             // 右旋转

        // 非递归操作原始函数,非虚函数,方便公有的add和del直接包装一下调用,可以降低耦合度
        TreeNode<T> * add_raw(const T & key);
        TreeNode<T> * del_raw(const T & key);
    };

#include <ttl/bs_tree.inl>

}
