#pragma once

#include <cstring>

namespace ttl
{
    template <typename T>
    class SkipListNode
    {
        typedef SkipListNode<T> Node;
    public:
        SkipListNode() = delete;
        SkipListNode(const T & value, int level) : m_value(value), m_level(level)
        {
            m_forward = new Node *[level];
            std::memset(m_forward, 0, sizeof(Node *) * level);
        }
        ~SkipListNode()
        {
            if (m_forward != nullptr)
            {
                delete [] m_forward;
                m_forward = nullptr;
            }
        }

    public:
        T m_value;
        int m_level;
        Node ** m_forward;      //每个节点都有一个下N个节点的数组
    };
}
