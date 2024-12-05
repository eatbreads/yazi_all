#pragma once

#include <vector>
#include <ttl/trie_node.h>

namespace ttl
{
    template <typename T>
    class TrieIterator
    {
        typedef TrieNode<T> Node;
        typedef TrieIterator<T> iterator;
        typedef std::vector<std::pair<Node *, int>> TrieStack;
    public:
        TrieIterator() : m_root(nullptr) {}
        TrieIterator(Node * root) : m_root(root) {}
        TrieIterator(Node * root, TrieStack & stack) : m_root(root)
        {
            m_stack.swap(stack);
        }
        ~TrieIterator() {}

        bool operator == (const iterator & other)
        {
            if (m_root != other.m_root)
                return false;
            if (m_stack.size() != other.m_stack.size())
                return false;
            if (m_stack.empty())
                return true;
            auto pair1 = m_stack.back();
            auto pair2 = other.m_stack.back();
            return (pair1.first == pair2.first && pair1.second == pair2.second);
        }

        bool operator != (const iterator & other)
        {
            if (m_root != other.m_root)
                return true;
            if (m_stack.size() != other.m_stack.size())
                return true;
            if (m_stack.empty())
                return false;
            auto pair1 = m_stack.back();
            auto pair2 = other.m_stack.back();
            return (pair1.first != pair2.first || pair1.second != pair2.second);
        }

        iterator & operator = (const iterator & other)
        {
            if (this == &other)
            {
                return *this;
            }
            m_root = other.m_root;
            m_stack = other.m_stack;
            return *this;
        }

        iterator & operator ++ ()
        {
            if (m_stack.empty())
            {
                m_root->first(m_stack);
                return *this;
            }
            auto pair = m_stack.back();
            auto node = pair.first->m_children[pair.second];
            node->successor(m_stack);
            return *this;
        }

        iterator operator ++ (int)
        {
            iterator it = *this;
            ++(*this);
            return it;
        }

        iterator operator + (int n)
        {
            iterator it = *this;
            for (int i = 0; i < n; i++)
            {
                ++it;
            }
            return it;
        }

        iterator & operator += (int n)
        {
            for (int i = 0; i < n; i++)
            {
                ++(*this);
            }
            return *this;
        }

        iterator & operator -- ()
        {
            if (m_stack.empty())
            {
                m_root->last(m_stack);
                return *this;
            }
            auto pair = m_stack.back();
            auto node = pair.first->m_children[pair.second];
            node->predecessor(m_stack);
            return *this;
        }

        iterator operator -- (int)
        {
            iterator it = *this;
            --(*this);
            return it;
        }

        iterator operator - (int n)
        {
            iterator it = *this;
            for (int i = 0; i < n; i++)
            {
                --it;
            }
            return it;
        }

        iterator & operator -= (int n)
        {
            for (int i = 0; i < n; i++)
            {
                --(*this);
            }
            return *this;
        }

        T & operator * ();

        T * operator -> ()
        {
            return &(operator*());
        }

    private:
        Node * m_root;
        TrieStack m_stack;
        T m_data;
    };

    template <typename T>
    T & TrieIterator<T>::operator * ()
    {
        string data;
        for (int i = 0; i < m_stack.size(); i++)
        {
            auto pair = m_stack[i];
            auto node = pair.first->m_children[pair.second];
            data.push_back(node->m_data);
        }
        if (std::is_same<T, uint8_t>::value ||
            std::is_same<T, uint16_t>::value ||
            std::is_same<T, uint32_t>::value)
        {
            m_data = std::strtol(data.c_str(), nullptr, 10);
        }
        else if (std::is_same<T, uint64_t>::value)
        {
            m_data = std::strtoll(data.c_str(), nullptr, 10);
        }
        return m_data;
    }

    template <>
    string & TrieIterator<string>::operator * ()
    {
        m_data.clear();
        for (int i = 0; i < m_stack.size(); i++)
        {
            auto pair = m_stack[i];
            auto node = pair.first->m_children[pair.second];
            m_data.push_back(node->m_data);
        }
        return m_data;
    }
}