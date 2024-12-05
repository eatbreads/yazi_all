#pragma once

namespace ttl
{
    template <typename T, int N>
    class DequeNode
    {
    public:
        DequeNode() : m_data(nullptr), m_head(0), m_tail(0)
        {
            m_data = new T[N];
        }
        ~DequeNode()
        {
            if (m_data != nullptr)
            {
                delete [] m_data;
                m_data = nullptr;
            }
        }

    public:
        T * m_data;//注意每个节点都相当于一个数组
        int m_head;
        int m_tail;
    };
}
 