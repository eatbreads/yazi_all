#pragma once

#include <iostream>
#include <ttl/deque.h>

namespace ttl
{
    template <typename T, typename Container = Deque<T>>
    class Queue
    {
        friend class Digraph;
    public:
        Queue();
        ~Queue();

        void push(const T & value);
        void pop();
        T & front();
        const T & front() const;
        T & back();
        const T & back() const;
        int size() const;
        bool empty() const;
        void swap(Queue<T, Container> & other);
        void show() const;

    private:
        Container m_container;
    };

#include <ttl/queue.inl>

}
