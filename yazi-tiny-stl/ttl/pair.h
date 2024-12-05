#pragma once

#include <sstream>

namespace ttl
{
    template <typename K, typename V>
    class Pair
    {
    public:
        Pair() : first(K()), second(V()) {}
        Pair(const K & key, const V & value) : first(key), second(value) {}
        Pair(const Pair<K, V> & pair) : first(pair.first), second(pair.second) {}
        ~Pair() {}

        bool operator == (const Pair<K, V> & other) const
        {
            return first == other.first;
        }

        bool operator != (const Pair<K, V> & other) const
        {
            return first != other.first;
        }

        bool operator < (const Pair<K, V> & other) const
        {
            return first < other.first;
        }

        bool operator > (const Pair<K, V> & other) const
        {
            return first > other.first;
        }

        Pair<K, V> & operator = (const Pair<K, V> & other)
        {
            if (this == &other)
            {
                return *this;
            }
            first = other.first;
            second = other.second;
            return *this;
        }

        friend std::ostream & operator << (std::ostream & os, const Pair<K, V> & pair)
        {
            os << "(" << pair.first << ":" << pair.second << ")";
            return os;
        }

    public:
        K first;
        V second;
    };
}