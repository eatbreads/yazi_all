#pragma once

#include <ttl/bb_tree_node.h>

namespace ttl
{
    template <typename T, int t>
    class BBTreeIndexNode : public BBTreeNode<T, t>
    {
        typedef BBTreeNode<T, t> Node;
    public:
        BBTreeIndexNode() = delete;
        BBTreeIndexNode(Node * parent);
        virtual ~BBTreeIndexNode();

        virtual Node * create(Node * parent);
        virtual void insert(const T & key);
        virtual void take_from_left();
        virtual void take_from_right();
        virtual void merge();
        virtual bool remove(const T & key);
    };

#include <ttl/bb_tree_index_node.inl>
}