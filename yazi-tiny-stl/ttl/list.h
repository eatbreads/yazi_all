#pragma once

#include <iostream>
#include <stdexcept>
#include <ttl/list_node.h>
#include <ttl/list_iterator.h>
#include <ttl/list_const_iterator.h>
#include <ttl/list_reverse_iterator.h>

namespace ttl
{
    template <typename T>
    class List
    {
        typedef ListNode<T> Node;
    public:
        typedef ListIterator<T> iterator;
        typedef ListConstIterator<T> const_iterator;
        typedef ListReverseIterator<T> reverse_iterator;
    public:
        List();
        List(const List<T> & other);
        ~List();

        void assign(int n, const T & value);
        bool empty() const;
        int size() const;
        void show() const;

        void push_back(const T & value);
        void push_front(const T & value);
        void pop_back();
        void pop_front();
        T & front();
        const T & front() const;

        T & back();
        const T & back() const;

        void remove(const T & value);
        void clear();
        void resize(int size);
        void merge(List<T> & other);
        void reverse();
        void swap(List<T> & other);

        List<T> & operator = (const List<T> & other);

        iterator begin();
        iterator end();
        iterator insert(iterator pos, const T & value);
        iterator insert(iterator pos, int n, const T & value);
        iterator erase(iterator pos);
        iterator erase(iterator first, iterator last);
        iterator find(const T & value);

        const_iterator cbegin() const;
        const_iterator cend() const;
        const_iterator find(const T & value) const;

        reverse_iterator rbegin();
        reverse_iterator rend();
        reverse_iterator rfind(const T & value);

    private:
        Node * m_head;
        Node * m_tail;
        int m_size;
    };

#include <ttl/list.inl>

}
