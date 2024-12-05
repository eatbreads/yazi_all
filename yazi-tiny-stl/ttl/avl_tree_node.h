#pragma once

#include <ttl/bs_tree_node.h>

namespace ttl
{
    template <typename T>
    class AVLTreeNode : public BSTreeNode<T>
    {
    public:
        AVLTreeNode() = delete;
        AVLTreeNode(const T & key) : BSTreeNode<T>(key), m_height(1) {}
        virtual ~AVLTreeNode() {}

    public:
        int m_height;
    };
}
 