#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <ttl/skip_list_node.h>
#include <ttl/skip_list_iterator.h>
#include <ttl/skip_list_const_iterator.h>

namespace ttl
{
    template <typename T, int max_level>
    class SkipList
    {
        friend class Digraph;
        typedef SkipListNode<T> Node;
    public:
        typedef SkipListIterator<T> iterator;
        typedef SkipListConstIterator<T> const_iterator;
    public:
        SkipList();
        SkipList(float p);
        ~SkipList();

        bool empty() const;
        int size() const;

        bool insert(const T & value);
        void remove(const T & value);
        T & front();
        const T & front() const;
        T & back();
        const T & back() const;
        void clear();
        void show() const;

        iterator begin();
        iterator end();
        iterator find(const T & value);

        const_iterator cbegin() const;
        const_iterator cend() const;
        const_iterator find(const T & value) const;

    private:
        int random_level();
        Node * search(const T & value);

    private:
        Node * m_head;
        int m_level;        // current level of skip list
        int m_size;         // current element count of skip list
        float m_p;          // the fraction of the nodes with level
        //表示跳表中每个节点增加其层级的概率,m_p的值通常在0.5左右，但这个值可以根据具体的应用场景进行调整。
        //较小的m_p值会生成较为紧凑的跳表，但可能降低搜索效率；较大的m_p值则会生成较为稀疏的跳表，提高搜索效率但可能增加空间开销。
    };

#include <ttl/skip_list.inl>

}
