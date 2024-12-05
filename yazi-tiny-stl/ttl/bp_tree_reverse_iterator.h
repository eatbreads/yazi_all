#pragma once

#include <ttl/bp_tree_node.h>
#include <ttl/bp_tree_leaf_node.h>
#include <ttl/pair.h>

namespace ttl
{
    template <typename T, typename D, int t>
    class BPTreeReverseIterator
    {
        typedef BPTreeNode<T, D, t> Node;
        typedef BPTreeReverseIterator<T, D, t> iterator;
    public:
        BPTreeReverseIterator() : m_pointer(nullptr), m_offset(0) {}
        BPTreeReverseIterator(Node * pointer, int offset) : m_pointer(pointer), m_offset(offset) {}
        ~BPTreeReverseIterator() {}

        bool operator == (const iterator & other)
        {
            return (m_pointer == other.m_pointer) && (m_offset == other.m_offset);
        }

        bool operator != (const iterator & other)
        {
            return (m_pointer != other.m_pointer) || (m_offset != other.m_offset);
        }

        iterator & operator = (const iterator & other)
        {
            if (this == &other)
            {
                return *this;
            }
            m_pointer = other.m_pointer;
            m_offset = other.m_offset;
            return *this;
        }

        iterator & operator ++ ()
        {
            m_offset--;
            if (m_offset < 0)
            {
                auto prev = ((BPTreeLeafNode<T, D, t> *)m_pointer)->m_prev;
                if (prev)
                {
                    m_pointer = prev;
                    m_offset = prev->m_size - 1;
                }
            }
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
            m_offset++;
            if (m_offset == m_pointer->m_size)
            {
                auto next = ((BPTreeLeafNode<T, D, t> *)m_pointer)->m_next;
                if (next)
                {
                    m_pointer = next;
                    m_offset = 0;
                }
            }
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

        Pair<T, D> & operator * ()
        {
            auto pointer = (BPTreeLeafNode<T, D, t> *)m_pointer;
            m_pair.first = pointer->m_keys[m_offset];
            m_pair.second = pointer->m_data[m_offset];
            return m_pair;
        }

        Pair<T, D> * operator->()
        {
            auto pointer = (BPTreeLeafNode<T, D, t> *)m_pointer;
            m_pair.first = pointer->m_keys[m_offset];
            m_pair.second = pointer->m_data[m_offset];
            return &m_pair;
        }

    private:
        Node * m_pointer;
        int m_offset;
        Pair<T, D> m_pair;
    };
}