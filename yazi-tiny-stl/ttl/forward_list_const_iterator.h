#pragma once

#include <ttl/forward_list_node.h>

namespace ttl
{
    template <typename T>
    class ForwardListConstIterator
    {
        typedef ForwardListNode<T> Node;                //和那个node同样统一操作
        typedef ForwardListConstIterator<T> iterator;   //这边同样也是把自己取名为iterator
    public:
        ForwardListConstIterator() : m_pointer(nullptr) {}
        ForwardListConstIterator(Node * pointer) : m_pointer(pointer) {}
        virtual ~ForwardListConstIterator() {}

    public:
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
            m_pointer = m_pointer->m_next;
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
