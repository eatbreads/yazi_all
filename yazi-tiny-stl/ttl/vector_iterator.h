#pragma once

namespace ttl
{
    template <typename T>
    class VectorIterator
    {
        typedef VectorIterator<T> iterator;
    public:
        VectorIterator() : m_pointer(nullptr) {}
        VectorIterator(T * pointer) : m_pointer(pointer) {}
        ~VectorIterator() {}

        bool operator == (const iterator & other) const
        {
            return m_pointer == other.m_pointer;
        }

        bool operator != (const iterator & other) const
        {
            return m_pointer != other.m_pointer;
        }

        iterator & operator = (const iterator & other)
        {
            if (this == &other)
            {
                return *this;
            }
            m_pointer = other.m_pointer;
            return *this;
        }

        // 前缀++
        iterator & operator ++ ()
        {
            m_pointer += 1;
            return *this;
        }

        // 后缀++
        iterator operator ++ (int)
        {
            iterator it = *this;
            ++(*this);
            return it;
        }

        iterator operator + (int n)
        {
            iterator it = *this;
            it.m_pointer += n;
            return it;
        }

        iterator & operator += (int n)
        {
            m_pointer += n;
            return *this;
        }

        // 前缀--
        iterator & operator -- ()
        {
            m_pointer -= 1;
            return *this;
        }

        // 后缀--
        iterator operator -- (int)
        {
            iterator it = *this;
            --(*this);
            return it;
        }

        iterator operator - (int n)
        {
            iterator it = *this;
            it.m_pointer -= n;
            return it;
        }

        iterator & operator -= (int n)
        {
            m_pointer -= n;
            return *this;
        }

        int operator - (const iterator & other) const
        {
            return m_pointer - other.m_pointer;
        }

        T & operator * ()
        {
            return *m_pointer;
        }

        T * operator -> ()
        {
            return m_pointer;
        }

    private:
        T * m_pointer;
    };
}
