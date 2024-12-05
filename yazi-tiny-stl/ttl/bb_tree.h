#pragma once

#include <ttl/bb_tree_node.h>
#include <ttl/bb_tree_index_node.h>
#include <ttl/bb_tree_leaf_node.h>
#include <ttl/bb_tree_iterator.h>
#include <ttl/bb_tree_const_iterator.h>
#include <ttl/bb_tree_reverse_iterator.h>

namespace ttl
{
    template <typename T, int t>
    class BBTree
    {
        friend class Digraph;
        typedef BBTreeNode<T, t> Node;
    public:
        typedef BBTreeIterator<T, t> iterator;
        typedef BBTreeConstIterator<T, t> const_iterator;
        typedef BBTreeReverseIterator<T, t> reverse_iterator;
    public:
        BBTree();
        ~BBTree();

        void insert(const T & key);
        bool search(const T & key);
        Node * lookup(const T & key, bool leaf = true);
        void remove(const T & key);
        void traverse();
        int size() const;
        bool empty() const;
        bool valid() const;
        void clear();
        void swap(BBTree<T, t> & other);

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
        void clear(Node * root);
        Node * create_node(Node * parent, bool leaf);

    protected:
        Node * m_root;              // point to root node
        int m_size;
    };

#include <ttl/bb_tree.inl>

}