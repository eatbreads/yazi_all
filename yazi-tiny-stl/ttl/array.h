#pragma once

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <ttl/array_iterator.h>
#include <ttl/array_const_iterator.h>
#include <ttl/array_reverse_iterator.h>

namespace ttl
{
    template <typename T, int N>
    class Array
    {
    public:
        typedef ArrayIterator<T> iterator;
        typedef ArrayConstIterator<T> const_iterator;
        typedef ArrayReverseIterator<T> reverse_iterator;
    public:
        Array();
        ~Array();

        int size() const;
        bool empty() const;
        void show() const;

        T * data();
        const T * data() const;

        void swap(Array<T, N> & other);
        void fill(const T & value); 

        T & front();
        const T & front() const;

        T & back();
        const T & back() const;

        T & at(int index);
        const T & at(int index) const;

        T & operator [] (int index);
        const T & operator [] (int index) const;

        iterator begin();
        iterator end();

        const_iterator cbegin() const;
        const_iterator cend() const;

        reverse_iterator rbegin();
        reverse_iterator rend();

    private:
        T m_data[N];//这边意味着这是分配在栈上的,如果这个类被new出来则才会分配到堆
    };

#include <ttl/array.inl>

}
