#pragma once

#include <ttl/bb_tree_node.h>

namespace ttl
{
    template <typename T, int t>
    class BBTreeLeafNode : public BBTreeNode<T, t>
    {
        typedef BBTreeNode<T, t> Node;
    public:
        BBTreeLeafNode() = delete;
        BBTreeLeafNode(Node * parent);
        virtual ~BBTreeLeafNode();

        virtual Node * create(Node * parent);
        virtual void insert(const T & key);
        virtual void take_from_left();
        virtual void take_from_right();
        virtual void merge();
        virtual bool remove(const T & key);
    };

#include <ttl/bb_tree_leaf_node.inl>
}