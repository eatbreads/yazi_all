#pragma once

#include <ttl/bb_tree_node.h>

namespace ttl
{
    template <typename T, int t>
    class BBTreeConstIterator
    {
        typedef BBTreeNode<T, t> Node;
        typedef BBTreeConstIterator<T, t> iterator;
    public:
        BBTreeConstIterator() : m_pointer(nullptr), m_offset(0) {}
        BBTreeConstIterator(Node * pointer, int offset) : m_pointer(pointer), m_offset(offset) {}
        ~BBTreeConstIterator() {}

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
            if (m_offset == m_pointer->m_size)
            {
                return *this;
            }
            if (m_pointer->m_leaf)
            {
                m_offset++;
                while (m_pointer->m_parent && m_offset == m_pointer->m_size)
                {
                    m_offset = m_pointer->m_index;
                    m_pointer = m_pointer->m_parent;
                    ++(*this);
                }
            }
            else
            {
                m_pointer = m_pointer->m_children[m_offset + 1]->leftmost();
                m_offset = 0;
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
            if (m_offset == -1)
            {
                return *this;
            }
            if (m_pointer->m_leaf)
            {
                m_offset--;
                while (m_pointer->m_parent && m_offset == -1)
                {
                    m_offset = m_pointer->m_index - 1;
                    m_pointer = m_pointer->m_parent;
                    --(*this);
                }
            }
            else
            {
                m_pointer = m_pointer->m_children[m_offset]->rightmost();
                m_offset = m_pointer->m_size - 1;
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

        const T & operator * () const
        {
            return m_pointer->m_keys[m_offset];
        }

        const T * operator->() const
        {
            return &(m_pointer->m_keys[m_offset]);
        }

    private:
        Node * m_pointer;
        int m_offset;
    };
}