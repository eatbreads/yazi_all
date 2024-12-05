#pragma once

#include <ttl/bp_tree_node.h>

namespace ttl
{
    template <typename T, typename D, int t>
    class BPTreeIndexNode : public BPTreeNode<T, D, t>
    {
        typedef BPTreeNode<T, D, t> Node;
    public:
        BPTreeIndexNode() = delete;
        BPTreeIndexNode(Node * parent);
        virtual ~BPTreeIndexNode();

        virtual Node * create(Node * parent);
        virtual void insert(const T & key, const D & data);
        virtual void take_from_left();
        virtual void take_from_right();
        virtual void merge();
        virtual bool remove(const T & key);
    };

#include <ttl/bp_tree_index_node.inl>

}