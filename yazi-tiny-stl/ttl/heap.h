#pragma once

#include <iostream>
#include <ttl/vector.h>
#include <ttl/functor.h>

namespace ttl
{
    template <typename T, typename Container = Vector<T>, typename Compare = Less<T>>
    class Heap
    {
        friend class Digraph; 
    public:
        Heap();
        ~Heap();

        void push(const T & value);
        void pop();
        const T & top() const;
        bool empty() const;
        int size() const;
        void swap(Heap<T, Container, Compare> & other);
        void show() const;

    private:
        void heapify(int i);

    private:
        Container m_container;
        Compare m_compare;
    };

#include <ttl/heap.inl>

}
