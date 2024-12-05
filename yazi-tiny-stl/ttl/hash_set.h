#pragma once

#include <ttl/hash_table.h>

namespace ttl
{
    template <typename T, typename Hash = std::hash<T>, typename Container = HashTable<T, Hash>>
    class HashSet
    {
    public:
        typedef typename Container::iterator iterator;
        typedef typename Container::const_iterator const_iterator;
    public:
        HashSet();
        ~HashSet();

        bool insert(const T & key);
        bool remove(const T & key);
        bool search(const T & key);
        bool empty() const;
        int size() const;
        int bucket(const T & key) const;
        int bucket_count() const;
        int bucket_size(int slot) const;
        int count(const T & key) const;
        float load_factor() const;
        float max_load_factor() const;
        void max_load_factor(float f);
        Hash hash_function() const;
        void rehash(int n);
        void clear();
        void swap(HashSet<T, Hash, Container> & other);
        void show() const;

        iterator begin();
        iterator end();
        iterator find(const T & key);

        const_iterator cbegin() const;
        const_iterator cend() const;
        const_iterator find(const T & key) const;

    private:
        Container m_container;
    };

#include <ttl/hash_set.inl>

}