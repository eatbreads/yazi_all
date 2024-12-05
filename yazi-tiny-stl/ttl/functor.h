#pragma once

#include <functional>
#include <ttl/pair.h>

namespace ttl
{
    template <typename T>
    class Less
    {
    public:
        bool operator () (const T & x, const T & y) const
        {
            return x < y;
        }
    };

    template <typename T>
    class Greater 
    {
    public:
        bool operator () (const T & x, const T & y) const
        {
            return x > y;
        }
    };

    template <typename T>
    class Equal
    {
    public:
        bool operator () (const T & x, const T & y) const
        {
            return x == y;
        }
    };

    class PairHash
    {
    public:
        PairHash() = default;
        ~PairHash() = default;

        template <typename K, typename V>
        size_t operator () (const Pair<K, V> & pair)
        {
            std::hash<K> hash;
            return hash(pair.first);
        }
    };
}
