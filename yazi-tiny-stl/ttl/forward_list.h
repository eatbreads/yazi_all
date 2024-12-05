#pragma once

#include <iostream>
#include <stdexcept>
#include <ttl/forward_list_node.h>
#include <ttl/forward_list_iterator.h>
#include <ttl/forward_list_const_iterator.h>

namespace ttl
{
    template <typename T>
    class ForwardList
    {
        typedef ForwardListNode<T> Node;
    public:
        typedef ForwardListIterator<T> iterator;
        typedef ForwardListConstIterator<T> const_iterator;
    public:
        ForwardList();
        ~ForwardList();

        void assign(int n, const T & value);
        bool empty() const;
        int size() const;
        void show() const;

        void push_front(const T & value);
        void pop_front();

        void push_back(const T & value);
        void pop_back();

        T & front();
        const T & front() const;

        T & back();
        const T & back() const;

        void remove(const T & value);
        void clear();
        void resize(int size);
        void merge(ForwardList<T> & other);
        void swap(ForwardList<T> & other);

        ForwardList<T> & operator = (const ForwardList<T> & other);

        iterator begin();
        iterator end();

        iterator insert_after(iterator pos, const T & value);
        iterator insert_after(iterator pos, int n, const T & value);

        iterator erase_after(iterator pos);
        iterator erase_after(iterator first, iterator last);

        const_iterator cbegin() const;
        const_iterator cend() const;

    private:
        Node * m_head;
        Node * m_tail;
        int m_size;
    };

#include <ttl/forward_list.inl>

}
