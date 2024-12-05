#pragma once

#include <ttl/vector.h>
#include <ttl/deque_node.h>
#include <ttl/deque_iterator.h>
#include <ttl/deque_const_iterator.h>
#include <ttl/deque_reverse_iterator.h>

namespace ttl
{
    template <typename T, int N = 8>
    class Deque
    {
        friend class Digraph;
        typedef DequeNode<T, N> Node;
    public: 
        typedef DequeIterator<T, N> iterator;
        typedef DequeConstIterator<T, N> const_iterator;
        typedef DequeReverseIterator<T, N> reverse_iterator;
    public:
        Deque();
        ~Deque();

        void assign(int n, const T & value);
        int size() const;
        bool empty() const;
        void show() const;

        void push_front(const T & value);
        void push_back(const T & value);
        void pop_front();
        void pop_back();

        T & front();
        const T & front() const;

        T & back();
        const T & back() const;

        T & at(int index);
        const T & at(int index) const;

        T & operator [] (int index);
        const T & operator [] (int index) const;

        void resize(int n);
        void resize(int n, const T & value);
        void clear();
        void swap(Deque<T, N> & other);

        Deque<T, N> & operator = (const Deque<T, N> & other);

        iterator begin();
        iterator end();
        iterator insert(iterator pos, const T & value);
        iterator erase(iterator pos);

        const_iterator cbegin() const;
        const_iterator cend() const;

        reverse_iterator rbegin();
        reverse_iterator rend();

    private:
        Vector<Node *> m_nodes;//这边相当于二维数组,就是中控数组
        int m_size;     //表示元素个数
    };

#include <ttl/deque.inl>

}
