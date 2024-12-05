#pragma once

#include <cstring>
#include <stdexcept>

namespace ttl
{
    template <typename T, typename D, int t>
    class BPTreeNode
    {
        typedef BPTreeNode<T, D, t> Node;
    public:
        BPTreeNode() = delete;
        BPTreeNode(Node * parent, bool leaf);
        virtual ~BPTreeNode();

        bool thin() const;
        bool full() const;
        bool empty() const;
        void show() const;
        Node * search(const T & key);
        void traverse();
        void split(int i);
        void split_child(int i);
        Node * leftmost();
        Node * rightmost();
        int fill(int i);
        T predecessor(int i);
        T successor(int i);

        virtual Node * create(Node * parent) = 0;
        virtual void insert(const T & key, const D & data) = 0;
        virtual void take_from_left() = 0;
        virtual void take_from_right() = 0;
        virtual void merge() = 0;
        virtual bool remove(const T & key) = 0;

    public:
        T * m_keys;                 // an array of keys
        Node * m_parent;            // parent pointer
        Node ** m_children;         // an array of child pointers
        int m_size;                 // number of keys
        int m_index;                // index of this node
        bool m_leaf;
    };

#include <ttl/bp_tree_node.inl>

}