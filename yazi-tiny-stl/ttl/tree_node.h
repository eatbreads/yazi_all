#pragma once

namespace ttl
{
    template <typename T>
    class TreeNode
    {
        typedef TreeNode<T> Node;
    public:
        TreeNode() = delete;
        TreeNode(const T & key) : m_parent(nullptr), m_left(nullptr), m_right(nullptr), m_key(key) {}
        virtual ~TreeNode() {}

        Node * search(const T & key);//二分查找
        Node * leftmost();//寻找最左边最右边的叶子节点
        Node * rightmost();
        Node * predecessor();
        Node * successor();

    public:
        Node * m_parent;
        Node * m_left;
        Node * m_right;
        T m_key;
    };

    template <typename T>
    typename TreeNode<T>::Node * TreeNode<T>::search(const T & key)//这个即为二分查找
    {
        auto node = this;
        while (node != nullptr)
        {
            if (node->m_key == key)
                break;
            else if (node->m_key > key)
                node = node->m_left;
            else
                node = node->m_right;
        }
        return node;
    }

    template <typename T>
    typename TreeNode<T>::Node * TreeNode<T>::leftmost()
    {
        // find the leftmost leaf node
        auto node = this;
        while (node != nullptr)
        {
            if (node->m_left == nullptr)
            {
                break;
            }
            node = node->m_left;
        }
        return node;
    }

    template <typename T>
    typename TreeNode<T>::Node * TreeNode<T>::rightmost()
    {
        // find the rightmost leaf node
        Node * node = this;
        while (node != nullptr)
        {
            if (node->m_right == nullptr)
            {
                break;
            }
            node = node->m_right;
        }
        return node;
    }

    template <typename T>
    typename TreeNode<T>::Node * TreeNode<T>::predecessor()
    {
        if (m_left != nullptr)          //当当前节点是作为右孩子时
            return m_left->rightmost();//即找比他小的(前驱),即为左子树的最右叶子节点

        auto node = m_parent;
        while (node != nullptr)
        {
            if (node->m_key < m_key)
            {
                break;
            }
            node = node->m_parent;//这里就不用讨论父节点的最右叶子节点了,因为会到这一步,当前节点必然是左节点
        }
        return node;
    }

    template <typename T>
    typename TreeNode<T>::Node * TreeNode<T>::successor()
    {
        if (m_right != nullptr)
            return m_right->leftmost();//翻转过来而已

        auto node = m_parent;
        while (node != nullptr)
        {
            if (node->m_key > m_key)
            {
                break;
            }
            node = node->m_parent;
        }
        return node;
    }
}
