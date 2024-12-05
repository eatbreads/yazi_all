#pragma once

#include <ttl/skip_list_node.h>

namespace ttl
{
    template <typename T>//迭代器和普通的没区别,就是很正常的迭代器
    class SkipListIterator
    {
        typedef SkipListNode<T> Node;
        typedef SkipListIterator<T> iterator;
    public:
        SkipListIterator() : m_pointer(nullptr) {}
        SkipListIterator(Node * pointer) : m_pointer(pointer) {}
        ~SkipListIterator() {}

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

        T & operator * ()
        {
            return m_pointer->m_value;
        }

        T * operator -> ()
        {
            return &(m_pointer->m_value);
        }

    private:
        Node * m_pointer;
    };
}
