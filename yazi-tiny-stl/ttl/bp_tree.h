#pragma once

#include <ttl/bp_tree_node.h>
#include <ttl/bp_tree_index_node.h>
#include <ttl/bp_tree_leaf_node.h>
#include <ttl/bp_tree_iterator.h>
#include <ttl/bp_tree_const_iterator.h>
#include <ttl/bp_tree_reverse_iterator.h>

namespace ttl
{
    template <typename T, typename D, int t>
    class BPTree
    {
        friend class Digraph;
        typedef BPTreeNode<T, D, t> Node;
    public:
        typedef BPTreeIterator<T, D, t> iterator;
        typedef BPTreeConstIterator<T, D, t> const_iterator;
        typedef BPTreeReverseIterator<T, D, t> reverse_iterator;
    public:
        BPTree();
        ~BPTree();

        void insert(const T & key, const D & data);
        bool search(const T & key);
        Node * lookup(const T & key, bool leaf = true);
        void remove(const T & key);
        void traverse();
        int size() const;
        bool empty() const;
        bool valid() const;
        void clear();
        void swap(BPTree<T, D, t> & other);

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

#include <ttl/bp_tree.inl>

}