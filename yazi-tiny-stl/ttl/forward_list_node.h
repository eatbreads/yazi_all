#pragma once

namespace ttl
{
    template <typename T>
    class ForwardListNode
    {
        typedef ForwardListNode<T> Node;        //把自身取了个别名Node
    public:
        ForwardListNode() = delete;
        ForwardListNode(const T & value) : m_value(value), m_next(nullptr) {}
        ~ForwardListNode() {}

    public:
        T m_value;
        Node * m_next;
    };
}
