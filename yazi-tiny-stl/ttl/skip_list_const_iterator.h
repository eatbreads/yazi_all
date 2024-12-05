#pragma once

#include <ttl/skip_list_node.h>

namespace ttl
{
    template <typename T>
    class SkipListConstIterator
    {
        typedef SkipListNode<T> Node;
        typedef SkipListConstIterator<T> iterator;
    public:
        SkipListConstIterator() : m_pointer(nullptr) {}
        SkipListConstIterator(Node * pointer) : m_pointer(pointer) {}
        ~SkipListConstIterator() {}

        bool operator == (const iterator & other)
        {
            return m_pointer == other.m_pointer;
        }

        bool operator != (const iterator & other)
        {
            return m_pointer != other.m_pointer;
        }

        iterator & operator = (const iterator & other)
        {
            if (this == &other)
            {
                return *this;
            }
            m_pointer = other.m_pointer;
            return *this;
        }

        iterator & operator ++ ()
        {
            m_pointer = m_pointer->m_forward[0];
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

        const T & operator * ()
        {
            return m_pointer->m_value;
        }

        const T * operator -> ()
        {
            return &(m_pointer->m_value);
        }

    private:
        Node * m_pointer;
    };
}
