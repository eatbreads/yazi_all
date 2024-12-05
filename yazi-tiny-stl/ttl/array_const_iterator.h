#pragma once

namespace ttl
{
    template <typename T>
    class ArrayConstIterator
    {
        typedef ArrayConstIterator<T> iterator;
    public:
        ArrayConstIterator() : m_pointer(nullptr) {}
        ArrayConstIterator(T * pointer) : m_pointer(pointer) {}
        ~ArrayConstIterator() {}

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
            if (this == & other)
            {
                return *this;
            }
            m_pointer = other.m_pointer;
            return *this;
        }

        // 前缀++
        iterator & operator ++ ()//为什么这边允许进行加减操作
        {                       //因为cend这种只是不允许修改所指的对象,相当于底层指针,它自身是可以移动的
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

        const T & operator * ()
        {
            return *m_pointer;
        }

        const T * operator -> ()//这个是编译器支持的,他执行之后实际上会获得T?而不是T*?
        {                       //这个和普通迭代器的区别就是解引用和箭头是返回const T的,即所指不能修改
            return m_pointer;
        }

    private:
        T * m_pointer;
    };
}
