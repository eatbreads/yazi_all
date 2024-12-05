#pragma once

#include <vector>

namespace ttl
{
    template <typename T>
    class TrieNode
    {
        typedef TrieNode<T> Node;
        typedef std::vector<std::pair<Node *, int>> TrieStack;
    public:
        TrieNode();
        ~TrieNode();

        void insert(int idx, Node * child);
        void remove(int idx);

        void first(TrieStack & stack);
        void last(TrieStack & stack);
        void predecessor(TrieStack & stack);
        void successor(TrieStack & stack);

    public:
        char m_data;
        bool m_flag;
        Node ** m_children;
        int m_size;
    };

#include <ttl/trie_node.inl>
}