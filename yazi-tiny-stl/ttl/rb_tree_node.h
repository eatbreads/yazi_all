#pragma once

#include <ttl/bs_tree_node.h>

namespace ttl
{
    template <typename T>
    class RBTreeNode : public BSTreeNode<T>
    {
    public:
        RBTreeNode() = delete;
        RBTreeNode(const T & key) : BSTreeNode<T>(key), m_color('R') {}
        virtual ~RBTreeNode() {}

    public:
        char m_color;
    };
}
