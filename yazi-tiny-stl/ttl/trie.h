#pragma once

#include <cstdint>
#include <typeinfo>
#include <string>
using std::string;
#include <type_traits>

#include <ttl/trie_node.h>
#include <ttl/trie_iterator.h>
#include <ttl/trie_const_iterator.h>
#include <ttl/trie_reverse_iterator.h>

namespace ttl
{
    template <typename T>
    class Trie
    {
        friend class Digraph;
        typedef TrieNode<T> Node;
        typedef std::vector<std::pair<Node *, int>> TrieStack;
    public:
        typedef TrieIterator<T> iterator;
        typedef TrieConstIterator<T> const_iterator;
        typedef TrieReverseIterator<T> reverse_iterator;

        static_assert(
                std::is_same<T, uint8_t>::value ||
                std::is_same<T, uint16_t>::value ||
                std::is_same<T, uint32_t>::value ||
                std::is_same<T, uint64_t>::value ||
                std::is_same<T, string>::value,
                "trie supports only uint8, uint16, uint32, uint64, string types.");

    public:
        Trie();
        ~Trie();

        void insert(const T & key);
        bool search(const T & key);
        bool prefix(const T & key);
        void remove(const T & key);
        int size() const;
        bool empty() const;
        void clear();
        void swap(Trie<T> & other);

        iterator begin();
        iterator end();
        iterator find(const T & key);

        const_iterator cbegin() const;
        const_iterator cend() const;
        const_iterator find(const T & key) const;

        reverse_iterator rbegin();
        reverse_iterator rend();
        reverse_iterator rfind(const T & key);

    protected:
        void insert(const char * data, int size);
        void remove(const char * data, int size);
        Node * search(const char * data, int size);
        bool find(const char * data, int size, TrieStack & stack) const;

    private:
        Node * m_root;
        int m_size;
    };

#include <ttl/trie.inl>
}