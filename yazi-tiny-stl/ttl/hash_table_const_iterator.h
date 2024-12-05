#pragma once

#include <ttl/hash_table_node.h>

namespace ttl
{
    template <typename T>
    class HashTableConstIterator
    {
        typedef HashTableNode<T> Node;
        typedef HashTableConstIterator<T> iterator;
    public:
        HashTableConstIterator() : m_buckets(nullptr), m_node(nullptr), m_bucket_count(0), m_slot(0) {}
        HashTableConstIterator(Node ** buckets, Node * node, int bucket_count, int slot) : m_buckets(buckets), m_node(node), m_bucket_count(bucket_count), m_slot(slot) {}
        ~HashTableConstIterator() {}

        bool operator == (const iterator & other)
        {
            return (m_buckets == other.m_buckets &&
                    m_node == other.m_node &&
                    m_bucket_count == other.m_bucket_count &&
                    m_slot == other.m_slot);
        }

        bool operator != (const iterator & other)
        {
            return (m_buckets != other.m_buckets ||
                    m_node != other.m_node ||
                    m_bucket_count != other.m_bucket_count ||
                    m_slot != other.m_slot);
        }

        iterator & operator = (const iterator & other)
        {
            if (this == &other)
            {
                return *this;
            }
            m_buckets == other.m_buckets;
            m_node == other.m_node;
            m_bucket_count == other.m_bucket_count;
            m_slot == other.m_slot;
            return *this;
        }

        iterator & operator ++ ()
        {
            if (m_node->m_next != nullptr)
            {
                m_node = m_node->m_next;
            }
            else
            {
                m_node = nullptr;
                m_slot++;
                while (m_slot < m_bucket_count)
                {
                    if (m_buckets[m_slot] != nullptr)
                    {
                        m_node = m_buckets[m_slot];
                        break;
                    }
                    m_slot++;
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

        const T & operator * ()
        {
            return m_node->m_key;
        }

        const T * operator -> ()
        {
            return &(m_node->m_key);
        }

    private:
        Node ** m_buckets;
        Node * m_node;
        int m_bucket_count;
        int m_slot;
    };
}