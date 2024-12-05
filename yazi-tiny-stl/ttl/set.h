#pragma once

#include <ttl/rb_tree.h>

namespace ttl
{
    template <typename T, typename Container = RBTree<T>>
    class Set
    {
    public:
        typedef typename Container::iterator iterator;
        typedef typename Container::const_iterator const_iterator;
        typedef typename Container::reverse_iterator reverse_iterator;
    public:
        Set();
        ~Set();

        int size() const;
        int count(const T & key) const;
        bool empty() const;
        void clear();
        void insert(const T & key);
        void remove(const T & key);
        void swap(Set<T, Container> & other);

        iterator begin();
        iterator end();
        iterator find(const T & key);

        const_iterator cbegin() const;
        const_iterator cend() const;
        const_iterator find(const T & key) const;

        reverse_iterator rbegin();
        reverse_iterator rend();
        reverse_iterator rfind(const T & key);

    private:
        Container m_container;
    };

#include <ttl/set.inl>

}