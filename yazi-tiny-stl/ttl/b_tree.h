#pragma once

#include <ttl/b_tree_node.h>
#include <ttl/b_tree_iterator.h>
#include <ttl/b_tree_const_iterator.h>
#include <ttl/b_tree_reverse_iterator.h>

namespace ttl
{
    template <typename T, int t>
    class BTree
    {
        friend class Digraph;
        typedef BTreeNode<T, t> Node;
    public:
        typedef BTreeIterator<T, t> iterator;
        typedef BTreeConstIterator<T, t> const_iterator;
        typedef BTreeReverseIterator<T, t> reverse_iterator;
    public:
        BTree();
        ~BTree();

        void insert(const T & key);
        bool search(const T & key);
        Node * lookup(const T & key);
        void remove(const T & key);
        void traverse();
        int size() const;
        bool empty() const;
        bool valid() const;
        void clear();
        void swap(BTree<T, t> & other);

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

    private:
        Node * m_root;
        int m_size;
    };

#include <ttl/b_tree.inl>

}