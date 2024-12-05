#pragma once

namespace ttl
{
    template <typename T>
    class HashTableNode//哈希的节点
    {
        typedef HashTableNode<T> Node;
    public:
        HashTableNode() : m_key(T()), m_code(0), m_next(nullptr) {}
        HashTableNode(const T & key, size_t code) : m_key(key), m_code(code), m_next(nullptr) {}
        ~HashTableNode() {}

    public:
        T m_key;        
        size_t m_code;
        Node * m_next;  //用的是链表来实现,所以每个有一个指针

        
    };

}