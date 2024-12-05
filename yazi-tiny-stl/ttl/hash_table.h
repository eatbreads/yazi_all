#pragma once

#include <iostream>
#include <cstring>
#include <functional>
#include <ttl/hash_table_node.h>
#include <ttl/hash_table_iterator.h>
#include <ttl/hash_table_const_iterator.h>

namespace ttl
{
    template <typename T, typename Hash = std::hash<T>>//这边使用了标准库的哈希函数
    class HashTable
    {
        friend class Digraph;
        typedef HashTableNode<T> Node;
    public:
        typedef HashTableIterator<T> iterator;
        typedef HashTableConstIterator<T> const_iterator;
    public:
        HashTable();
        ~HashTable();

        bool insert(const T & key);
        bool remove(const T & key);
        bool search(const T & key); 
        bool empty() const;
        int size() const;
        int bucket(const T & key) const;
        int bucket_count() const;
        int bucket_size(int slot) const;
        
        int count(const T & key) const;
        float load_factor() const;
        float max_load_factor() const;
        void max_load_factor(float f);
        Hash hash_function() const;
        void rehash(int n);
        void clear();
        void swap(HashTable<T> & other);
        void show() const;

        iterator begin();
        iterator end();
        iterator find(const T & key);

        const_iterator cbegin() const;
        const_iterator cend() const;
        const_iterator find(const T & key) const;

    private: 
        bool check_prime(int n);
        int get_prime(int n);
        Node ** buckets_create(int bucket_count);
        bool buckets_insert(Node ** buckets, int bucket_count, const T & key);
        bool buckets_remove(Node ** buckets, int bucket_count, const T & key);
        Node * buckets_search(Node ** buckets, int bucket_count, const T & key);
        void buckets_migrate(Node ** buckets, int bucket_count, Node * node);
        void buckets_destroy(Node ** buckets, int bucket_count);

    private:
        Node ** m_buckets;      //相当于指针数组,那些桶都是指针形式存在
        int m_bucket_count;     //桶长度,被设置为质数
        int m_size;
        Hash m_hash;            //被赋值为stl的哈希函数
        float m_max_load_factor;//负载因子,unordered_map的负载因子是1
                                //表示桶数量和元素数量一致,元素多了就要加桶,
    };

#include <ttl/hash_table.inl>

}