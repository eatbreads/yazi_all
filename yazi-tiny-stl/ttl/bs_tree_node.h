#pragma once

#include <ttl/tree_node.h>

namespace ttl
{
    template <typename T>
    class BSTreeNode : public TreeNode<T>
    {
    public:
        BSTreeNode() = delete;
        BSTreeNode(const T & key) : TreeNode<T>(key) {}
        virtual ~BSTreeNode() {}
    };
}
 