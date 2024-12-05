#pragma once

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <typeinfo>
#include <ttl/vector_iterator.h>
#include <ttl/vector_const_iterator.h>
#include <ttl/vector_reverse_iterator.h>

namespace ttl
{
    template <typename T>
    class Vector
    {
    public:
        typedef VectorIterator<T> iterator;
        typedef VectorConstIterator<T> const_iterator;
        typedef VectorReverseIterator<T> reverse_iterator;
    public:
        Vector();
        Vector(const Vector<T> & other);
        ~Vector();

        void assign(int n, const T & value);
        void push_back(const T & value);
        void pop_back();
        void show() const;

        T & at(int index);
        const T & at(int index) const;

        T & front();
        const T & front() const;

        T & back();
        const T & back() const;

        bool empty() const;
        void clear();
        int size() const;
        int capacity() const;

        T * data();
        const T * data() const;

        T & operator [] (int index);
        const T & operator [] (int index) const;

        Vector<T> & operator = (const Vector<T> & other);

        void swap(Vector<T> & other);

        void resize(int n);
        void resize(int n, const T & value);
        void reserve(int n);

        iterator begin();
        iterator end();

        iterator insert(iterator pos, const T & value);
        iterator insert(iterator pos, int n, const T & value);

        iterator erase(iterator pos);
        iterator erase(iterator first, iterator last);

        const_iterator cbegin() const;
        const_iterator cend() const;

        reverse_iterator rbegin();
        reverse_iterator rend();

    private:
        bool is_basic_type();

    private:
        T * m_data;
        int m_size;
        int m_capacity;
    };

#include <ttl/vector.inl>

}
