#pragma once

#include <iostream>
#include <ttl/deque.h>

namespace ttl
{
    template <typename T, typename Container = Deque<T>>
    class Stack
    {
        friend class Digraph;
    public:
        Stack();
        ~Stack();

        void push(const T & value);
        void pop();
        T & top();
        const T & top() const;
        int size() const;
        bool empty() const;
        void swap(Stack<T, Container> & other);
        void show() const;

    private:
        Container m_container;
    };

#include <ttl/stack.inl>

}
