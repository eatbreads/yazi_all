#pragma once

#include <ttl/hash_table_node.h>

namespace ttl
{
    template <typename T>
    class HashTableIterator
    {
        typedef HashTableNode<T> Node;
        typedef HashTableIterator<T> iterator;
    public:
        HashTableIterator() : m_buckets(nullptr), m_node(nullptr), m_bucket_count(0), m_slot(0) {}
        HashTableIterator(Node ** buckets, Node * node, int bucket_count, int slot) : m_buckets(buckets), m_node(node), m_bucket_count(bucket_count), m_slot(slot) {}
        ~HashTableIterator() {}

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
            m_buckets = other.m_buckets;
            m_node = other.m_node;
            m_bucket_count = other.m_bucket_count;
            m_slot = other.m_slot;
            return *this;
        }

        iterator & operator ++ ()//所以这边遍历是要么寻找链表下一个,要么寻找新的一串链表然后再返回
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

        iterator operator ++ (int)//表示调用前置++
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
                ++it;//也是调用前置++
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
            return m_node->m_key;
        }

        T * operator -> ()
        {
            return &(m_node->m_key);
        }

    private:
        Node ** m_buckets;//指向指针的指针
        Node * m_node;      //这个表示指向的当前桶
        int m_bucket_count;
        int m_slot;         //当前槽位置
    };
}