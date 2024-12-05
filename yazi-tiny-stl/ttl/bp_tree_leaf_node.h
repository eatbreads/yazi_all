#pragma once

#include <ttl/bp_tree_node.h>

namespace ttl
{
    template <typename T, typename D, int t>
    class BPTreeLeafNode : public BPTreeNode<T, D, t>
    {
        typedef BPTreeNode<T, D, t> Node;
    public:
        BPTreeLeafNode() = delete;
        BPTreeLeafNode(Node * parent);
        virtual ~BPTreeLeafNode();

        virtual Node * create(Node * parent);
        virtual void insert(const T & key, const D & data);
        virtual void take_from_left();
        virtual void take_from_right();
        virtual void merge();
        virtual bool remove(const T & key);

    public:
        D * m_data;                     // an array of data
        Node * m_prev;                  // point to prev leaf node
        Node * m_next;                  // point to next leaf node
    };

#include <ttl/bp_tree_leaf_node.inl>

}