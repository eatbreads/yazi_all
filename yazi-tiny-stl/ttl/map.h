#pragma once

#include <ttl/pair.h>
#include <ttl/rb_tree.h>

namespace ttl
{
    template <typename K, typename V, typename Container = RBTree<Pair<K, V>>>
    class Map
    {
    public:
        typedef typename Container::iterator iterator;
        typedef typename Container::const_iterator const_iterator;
        typedef typename Container::reverse_iterator reverse_iterator;
    public:
        Map();
        ~Map();

        int size() const;
        int count(const K & key) const;
        bool empty() const;
        void clear();
        void insert(const Pair<K, V> & pair);
        void remove(const K & key);
        V & at(const K & key);
        const V & at(const K & key) const;
        void swap(Map<K, V, Container> & other);

        iterator begin();
        iterator end();
        iterator find(const K & key);

        const_iterator cbegin() const;
        const_iterator cend() const;
        const_iterator find(const K & key) const;

        reverse_iterator rbegin();
        reverse_iterator rend();
        reverse_iterator rfind(const K & key);

        V & operator [] (const K & key);

    private:
        Container m_container;
    };

#include <ttl/map.inl>

}