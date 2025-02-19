#pragma once

#include <ttl/tree_node.h>

namespace ttl
{
    template <typename T>
    class TreeConstIterator
    {
        typedef TreeNode<T> Node;
        typedef TreeConstIterator<T> iterator;
    public:
        TreeConstIterator() : m_root(nullptr), m_pointer(nullptr) {}
        TreeConstIterator(Node * root, Node * pointer) : m_root(root), m_pointer(pointer) {}
        ~TreeConstIterator() {}

        bool operator == (const iterator & other)
        {
            return (m_root == other.m_root) && (m_pointer == other.m_pointer);
        }

        bool operator != (const iterator & other)
        {
            return (m_root != other.m_root) || (m_pointer != other.m_pointer);
        }

        iterator & operator = (const iterator & other)
        {
            if (this == &other)
            {
                return *this;
            }
            m_root = other.m_root;
            m_pointer = other.m_pointer;
            return *this;
        }

        iterator & operator ++ ()
        {
            if (m_pointer == nullptr)
            {
                m_pointer = m_root->leftmost();
                return *this;
            }
            m_pointer = m_pointer->successor();
            return *this;
        }

        iterator operator ++ (int)
        {
            iterator it = *this;
            ++(*this);
            return it;
        }

        iterator operator + (int n)
        {
            iterator it = *this;
            for (int i = 0; i < n; i++)
            {
                ++it;
            }
            return it;
        }

        iterator & operator += (int n)
        {
            for (int i = 0; i < n; i++)
            {
                ++(*this);
            }
            return *this;
        }

        iterator & operator -- ()
        {
            if (m_pointer == nullptr)
            {
                m_pointer = m_root->rightmost();
                return *this;
            }
            m_pointer = m_pointer->predecessor();
            return *this;
        }

        iterator operator -- (int)
        {
            iterator it = *this;
            --(*this);
            return it;
        }

        iterator operator - (int n)
        {
            iterator it = *this;
            for (int i = 0; i < n; i++)
            {
                --it;
            }
            return it;
        }

        iterator & operator -= (int n)
        {
            for (int i = 0; i < n; i++)
            {
                --(*this);
            }
            return *this;
        }

        const T & operator * ()
        {
            return m_pointer->m_key;
        }

        const T * operator -> ()
        {
            return &(m_pointer->m_key);
        }

    private:
        Node * m_root;
        Node * m_pointer;
    };
}
