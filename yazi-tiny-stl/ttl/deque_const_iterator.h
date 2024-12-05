#pragma once

#include <ttl/deque_node.h>

namespace ttl
{
    template <typename T, int N>
    class DequeConstIterator
    {
        typedef DequeNode<T, N> Node;
        typedef DequeConstIterator<T, N> iterator;
    public:
        DequeConstIterator() : m_pointer(nullptr), m_offset(0) {}
        DequeConstIterator(Node ** pointer, int offset) : m_pointer(pointer), m_offset(offset) {}
        ~DequeConstIterator() {}

        bool operator == (const iterator & other) const
        {
            return (m_pointer == other.m_pointer) && (m_offset == other.m_offset);
        }

        bool operator != (const iterator & other) const
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

        // 前缀++
        iterator & operator ++ ()
        {
            m_offset++;
            return *this;
        }

        // 后缀++
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

        // 前缀--
        iterator & operator -- ()
        {
            m_offset--;
            return *this;
        }

        // 后缀--
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

        int operator - (const iterator & other) const
        {
            return m_offset - other.m_offset;
        }

        const T & operator * ()
        {
            Node * first = m_pointer[0];
            int first_size = first->m_tail - first->m_head;
            if (m_offset < first_size)
            {
                return first->m_data[first->m_head + m_offset];
            }
            int row = (m_offset - first_size) / N + 1;
            int col = (m_offset - first_size) % N;
            return m_pointer[row]->m_data[col];
        }

        const T * operator -> ()
        {
            return &(operator * ());
        }

    private:
        Node ** m_pointer;
        int m_offset;
    };
}
