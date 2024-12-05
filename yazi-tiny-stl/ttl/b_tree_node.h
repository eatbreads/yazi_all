#pragma once

#include <cstring>
#include <stdexcept>

namespace ttl
{
    template <typename T, int t>
    class BTreeNode
    {
        typedef BTreeNode<T, t> Node;
    public:
        BTreeNode() = delete;
        BTreeNode(Node * parent, bool leaf);
        ~BTreeNode();

        Node * leftmost();
        Node * rightmost();
        void take_from_left();
        void take_from_right();
        Node * search(const T & key);
        void insert(const T & key);
        void split(int i);
        void merge(int i);
        void fill(int i);
        bool thin() const;
        bool full() const;
        bool empty() const;
        void show() const;
        void traverse();
        bool remove(const T & key);
        bool remove_from_leaf(int i);
        bool remove_from_none_leaf(int i);
        T predecessor(int i);
        T successor(int i);

    public:
        T * m_keys;                 // an array of keys
        Node * m_parent;            // parent pointer
        Node ** m_children;         // an array of child pointers
        int m_size;                 // number of keys
        int m_index;                // index of this node
        bool m_leaf;
    };

#include <ttl/b_tree_node.inl>

}