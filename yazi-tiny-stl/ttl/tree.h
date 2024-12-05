#pragma once

#include <iostream>
#include <ttl/tree_node.h>
#include <ttl/tree_iterator.h>
#include <ttl/tree_const_iterator.h>
#include <ttl/tree_reverse_iterator.h>

namespace ttl
{
    template <typename T>
    class Tree
    {
        friend class Digraph;
        typedef TreeNode<T> Node;
    public:
        typedef TreeIterator<T> iterator;
        typedef TreeConstIterator<T> const_iterator;
        typedef TreeReverseIterator<T> reverse_iterator;
    public:
        Tree();
        virtual ~Tree();

        virtual void insert(const T & key) = 0;       // 插入
        virtual void remove(const T & key) = 0;       // 删除
        bool search(const T & key);                   // 查找
        int size() const;
        bool empty() const;
        bool valid() const;
        void clear();
        void swap(Tree<T> & other);
        void show() const;

        iterator begin();
        iterator end();
        iterator find(const T & key);

        const_iterator cbegin() const;
        const_iterator cend() const;
        const_iterator find(const T & key) const;

        reverse_iterator rbegin(); 
        reverse_iterator rend(); 
        reverse_iterator rfind(const T & key);

    protected:
        bool valid(Node * root) const;
        bool search(Node * root, const T & key);        // 递归查找
        void clear(Node * root);                        // 递归清空
        void preorder(Node * root) const;               // 前序遍历
        void inorder(Node * root) const;                // 中序遍历
        void postorder(Node * root) const;              // 后序遍历

        virtual Node * create_node(const T & key) = 0;
        virtual void delete_node(Node * node) = 0;

    protected:
        Node * m_root;
        int m_size;
    };

#include <ttl/tree.inl>

}
