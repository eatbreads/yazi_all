#pragma once

#include <ttl/pair.h>
#include <ttl/functor.h>
#include <ttl/hash_table.h>

namespace ttl
{
    template <typename K, typename V, typename Hash = PairHash, typename Container = HashTable<Pair<K, V>, Hash>>
    class HashMap
    {
        friend class Digraph;
    public:
        typedef typename Container::iterator iterator;
        typedef typename Container::const_iterator const_iterator;
    public:
        HashMap();
        ~HashMap();

        bool insert(const Pair<K, V> & pair);
        bool remove(const K & key);
        bool search(const K & key);
        bool empty() const;
        int size() const;
        V & at(const K & key);
        const V & at(const K & key) const;
        int bucket(const K & key) const;
        int bucket_count() const;
        int bucket_size(int slot) const;
        int count(const K & key) const;
        float load_factor() const;
        float max_load_factor() const;
        void max_load_factor(float f);
        Hash hash_function() const;
        void rehash(int n);
        void clear();
        void swap(HashMap<K, V, Hash, Container> & other);
        void show() const;

        iterator begin();
        iterator end();
        iterator find(const K & key);

        const_iterator cbegin() const;
        const_iterator cend() const;
        const_iterator find(const K & key) const;

        V & operator [] (const K & key);

    private:
        Container m_container;
    };

#include <ttl/hash_map.inl>

}