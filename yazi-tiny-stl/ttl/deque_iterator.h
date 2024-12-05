#pragma once

#include <ttl/deque_node.h>

namespace ttl
{
    template <typename T, int N>
    class DequeIterator
    {
        typedef DequeNode<T, N> Node;
        typedef DequeIterator<T, N> iterator;
    public:
        DequeIterator() : m_pointer(nullptr), m_offset(0) {}
        DequeIterator(Node ** pointer, int offset) : m_pointer(pointer), m_offset(offset) {}
        ~DequeIterator() {}

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
            m_offset++;//就是对偏移量++而已
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
                ++(*this);//这边感觉可以优化,而且这边是不会越界的,因为到时候解引用会计算实际上应该在哪一个节点
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

        T & operator * ()
        {
            Node * first = m_pointer[0];
            int first_size = first->m_tail - first->m_head;
            if (m_offset < first_size)
            {
                return first->m_data[first->m_head + m_offset];//在这个节点内部就直接返回
            }
            int row = (m_offset - first_size) / N + 1;//如果越界了就计算之后返回特定的
            int col = (m_offset - first_size) % N;
            return m_pointer[row]->m_data[col];
        }

        T * operator -> ()
        {
            return &(operator * ());//本质上调用了operator*()
        }

    private:
        Node ** m_pointer;//这个本质上是指向中控数组(vector)的指针,中控数组里面又是node*,所以是指针的指针
        int m_offset;       //然后遍历到哪个位置实际上是由offset决定的
    };
}
