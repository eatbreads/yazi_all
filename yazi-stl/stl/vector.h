#pragma once

#include <cstring>
#include <stdexcept>
#include <typeinfo>
//这个stdexcept是std的异常的头文件

namespace yazi
{
    namespace stl
    {
        template <typename T>
        class Vector
        {
        public:
            Vector();
            ~Vector();

            void push_back(const T & value);
            void pop_back();
            void show() const;

            T & at(int index);
            const T & at(int index) const;

            T & front();
            const T & front() const;

            T & back();
            const T & back() const;

            bool empty() const noexcept;
            void clear() noexcept;
            int size() const noexcept;
            int capacity() const noexcept;

            T * data() noexcept;
            const T * data() const noexcept;

            T & operator [] (int index);
            const T & operator [] (int index) const;

            Vector<T> & operator = (const Vector<T> & other);

            void swap(Vector<T> & other);

            void resize(int n);
            void resize(int n, const T & value);
            void reserve(int n);

            class iterator
            {
            public:
                iterator() : m_pointer(nullptr) {}
                iterator(T * pointer) : m_pointer(pointer) {}
                ~iterator() {}

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

                iterator operator + (int i)
                {
                    iterator it = *this;
                    it.m_pointer += i;
                    return it;
                }

                iterator & operator += (int i)
                {
                    m_pointer += i;
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

                iterator operator - (int i)
                {
                    iterator it = *this;
                    it.m_pointer -= i;
                    return it;
                }

                iterator & operator -= (int i)
                {
                    m_pointer -= i;
                    return *this;
                }
                //这边本质上是把内部的指针进行相减,指针相减会得到之间的元素个数
                int operator - (const iterator & other) const
                {
                    return m_pointer - other.m_pointer;
                }

                T & operator * ()
                {
                    return *m_pointer;  //这个很合理
                }

                T * operator -> ()      //迭代器这边居然->是返回指针吗
                {
                    return m_pointer;   //可能是编译器支持的,可以等价于调用m_pointer->next
                }

            private:
                T * m_pointer;          //这个迭代器内部的指针会一直移动来操作
            };

            iterator begin() noexcept;  //begin就是返回一个用data()来初始化的迭代器
            iterator end() noexcept;    //这边用尾元素的下一个元素来初始化

            class reverse_iterator  //这个就是反过来,+变成-
            {
            public:
                reverse_iterator() : m_pointer(nullptr) {}
                reverse_iterator(T * pointer) : m_pointer(pointer) {}
                ~reverse_iterator() {}

                bool operator == (const reverse_iterator & other) const
                {
                    return m_pointer == other.m_pointer;
                }

                bool operator != (const reverse_iterator & other) const
                {
                    return m_pointer != other.m_pointer;
                }

                reverse_iterator & operator = (const reverse_iterator & other)
                {
                    m_pointer = other.m_pointer;
                    return *this;
                }

                // 前缀++
                reverse_iterator & operator ++ ()
                {
                    m_pointer -= 1;
                    return *this;
                }

                // 后缀++
                reverse_iterator operator ++ (int)
                {
                    reverse_iterator it = *this;
                    ++(*this);
                    return it;
                }

                reverse_iterator operator + (int i)
                {
                    reverse_iterator it = *this;
                    it.m_pointer -= i;
                    return it;
                }

                reverse_iterator operator += (int i)
                {
                    m_pointer -= i;
                    return *this;
                }

                // 前缀--
                reverse_iterator & operator -- ()
                {
                    m_pointer += 1;
                    return *this;
                }

                // 后缀--
                reverse_iterator operator -- (int)
                {
                    reverse_iterator it = *this;
                    --(*this);
                    return it;
                }

                reverse_iterator operator - (int i)
                {
                    reverse_iterator it = *this;
                    it.m_pointer += i;
                    return it;
                }

                reverse_iterator & operator -= (int i)
                {
                    m_pointer += i;
                    return *this;
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

            reverse_iterator rbegin() noexcept;
            reverse_iterator rend() noexcept;
            //支持泛型算法
            iterator insert(iterator pos, const T & value);
            iterator insert(iterator pos, int n, const T & value);

            iterator erase(iterator pos);
            iterator erase(iterator first, iterator last);

        private:
            bool is_basic_type();

        private:
            T * m_data;
            int m_size;
            int m_capacity;
        };

        template <typename T>
        Vector<T>::Vector() : m_data(nullptr), m_size(0), m_capacity(0)
        {
        }

        template <typename T>
        Vector<T>::~Vector()
        {
            if (m_data != nullptr)
            {
                delete [] m_data;
                m_data = nullptr;
            }
            m_size = 0;
            m_capacity = 0;
        }

        template <typename T>
        void Vector<T>::push_back(const T & value)
        {
            if (m_size < m_capacity)
            {
                m_data[m_size] = value;
                m_size++;
                return;
            }

            // vector 扩容算法
            if (m_capacity == 0)
            {
                m_capacity = 1;
            }
            else
            {
                m_capacity *= 2;
            }
            T * data = new T[m_capacity];

            // 优化以后 -- start
            if (is_basic_type())
            {
                std::memcpy(data, m_data, m_size * sizeof(T));//但是这边直接拷贝内存就特别快
            }
            else
            {
                // 优化以前 -- start
                for (int i = 0; i < m_size; i++)
                {
                    data[i] = m_data[i];//就是说原本的方案都是扩容的时候要把原数组拷贝进新数组
                }
                // 优化以前 -- end
            }
            // 优化以后 -- end

            if (m_data != nullptr)
            {
                delete [] m_data;
                m_data = nullptr;
            }

            m_data = data;
            m_data[m_size] = value;
            m_size++;
        }

        template <typename T>
        void Vector<T>::pop_back()
        {
            if (m_size > 0)
            {
                m_size--;
            }
        }

        template <typename T>
        void Vector<T>::show() const
        {
            std::cout << "size=" << m_size << ", capacity=" << m_capacity << std::endl;
            for (int i = 0; i < m_size; i++)
            {
                std::cout << m_data[i] << ",";
            }
            std::cout << std::endl;
        }

        template <typename T>
        T & Vector<T>::at(int index)
        {
            if (index < 0 || index >= m_size)
            {
                throw std::logic_error("out of range");
            }
            return m_data[index];
        }

        template <typename T>
        const T & Vector<T>::at(int index) const
        {
            return at(index);
        }

        template <typename T>
        T & Vector<T>::front()
        {
            if (m_size <= 0)
            {
                throw std::logic_error("vector is empty");
            }
            return m_data[0];
        }

        template <typename T>
        const T & Vector<T>::front() const
        {
            return front();
        }

        template <typename T>
        T & Vector<T>::back()
        {
            if (m_size <= 0)
            {
                throw std::logic_error("vector is empty");
            }
            return m_data[m_size - 1];
        }

        template <typename T>
        const T & Vector<T>::back() const
        {
            return back();
        }

        template <typename T>
        bool Vector<T>::empty() const noexcept
        {
            return m_size == 0;
        }

        template <typename T>
        void Vector<T>::clear() noexcept
        {
            m_size = 0;
        }

        template <typename T>
        int Vector<T>::size() const noexcept
        {
            return m_size;
        }

        template <typename T>
        int Vector<T>::capacity() const noexcept
        {
            return m_capacity;
        }

        template <typename T>
        T * Vector<T>::data() noexcept
        {
            return m_data;
        }

        template <typename T>
        const T * Vector<T>::data() const noexcept
        {
            return data();
        }

        template <typename T>
        T & Vector<T>::operator [] (int index)
        {
            return at(index);
        }

        template <typename T>
        const T & Vector<T>::operator [] (int index) const
        {
            return at(index);
        }

        template <typename T>
        Vector<T> & Vector<T>::operator = (const Vector<T> & other)
        {
            if (m_capacity < other.m_size)
            {
                if (m_data != nullptr)
                {
                    delete [] m_data;
                    m_data = nullptr;
                    m_size = 0;
                    m_capacity = 0;
                }
                while (m_capacity < other.m_size)
                {
                    if (m_capacity == 0)
                    {
                        m_capacity = 1;
                    }
                    else
                    {
                        m_capacity *= 2;
                    }
                }
                m_data = new T[m_capacity];
            }
            // 优化以后 -- start
            if (is_basic_type())
            {
                std::memcpy(m_data, other.m_data, m_size * sizeof(T));
            }
            else
            {
                // 优化以前 -- start
                for (int i = 0; i < other.m_size; i++)
                {
                    m_data[i] = other.m_data[i];
                }
                // 优化以前 -- end
            }
            // 优化以后 -- end
            m_size = other.m_size;
            return *this;
        }

        template <typename T>
        void Vector<T>::swap(Vector<T> & other)
        {
            T * data = other.m_data;
            int size = other.m_size;
            int capacity = other.m_capacity;

            other.m_data = m_data;
            other.m_size = m_size;
            other.m_capacity = m_capacity;

            m_data = data;
            m_size = size;
            m_capacity = capacity;
        }

        template <typename T>
        void Vector<T>::resize(int n)
        {
            if (n < m_size)
            {
                m_size = n;
                return;
            }
            if (n <= m_capacity)
            {
                for (int i = m_size; i < n; i++)
                {
                    m_data[i] = T();        //这边调用了默认构造
                }
                m_size = n;
                return;
            }
            while (m_capacity < n)          //这边就是不一定保证cap只有那么大,但是一定够
            {
                if (m_capacity == 0)
                {
                    m_capacity = 1;
                }
                else
                {
                    m_capacity *= 2;
                }
            }

            T * data = new T[m_capacity];

            // 优化以后 -- start
            if (is_basic_type())
            {
                std::memcpy(data, m_data, m_size * sizeof(T));
            }
            else
            {
                // 优化以前 -- start
                for (int i = 0; i < m_size; i++)
                {
                    data[i] = m_data[i];
                }
                // 优化以前 -- end
            }
            // 优化以后 -- end

            for (int i = m_size; i < n; i++)
            {
                data[i] = T();
            }
            if (m_data != nullptr)
            {
                delete [] m_data;
                m_data = nullptr;
            }
            m_data = data;
            m_size = n;
        }

        template <typename T>
        void Vector<T>::resize(int n, const T & value)          //这边提供了拷贝的方式
        {
            if (n < m_size)
            {
                m_size = n;
                return;
            }
            if (n <= m_capacity)
            {
                for (int i = m_size; i < n; i++)
                {
                    m_data[i] = value;
                }
                m_size = n;
                return;
            }
            while (m_capacity < n)
            {
                if (m_capacity == 0)
                {
                    m_capacity = 1;
                }
                else
                {
                    m_capacity *= 2;
                }
            }

            T * data = new T[m_capacity];

            // 优化以后 -- start
            if (is_basic_type())
            {
                std::memcpy(data, m_data, m_size * sizeof(T));
            }
            else
            {
                // 优化以前 -- start
                for (int i = 0; i < m_size; i++)
                {
                    data[i] = m_data[i];
                }
                // 优化以前 -- end
            }
            // 优化以后 -- end

            for (int i = m_size; i < n; i++)
            {
                data[i] = value;
            }
            if (m_data != nullptr)
            {
                delete [] m_data;
                m_data = nullptr;
            }
            m_data = data;
            m_size = n;
        }

        template <typename T>
        void Vector<T>::reserve(int n)
        {
            if (m_capacity >= n)
            {
                return;
            }
            while (m_capacity < n)              //这个reserve也是并不保证大小就那么少,但是保证够
            {
                if (m_capacity == 0)
                {
                    m_capacity = 1;
                }
                else
                {
                    m_capacity *= 2;
                }
            }
            T * data = new T[m_capacity];
            // 优化以后 -- start
            if (is_basic_type())
            {
                std::memcpy(data, m_data, m_size * sizeof(T));
            }
            else
            {
                // 优化以前 -- start
                for (int i = 0; i < m_size; i++)
                {
                    data[i] = m_data[i];
                }
                // 优化以前 -- end
            }
            // 优化以后 -- end
            if (m_data != nullptr)
            {
                delete [] m_data;
                m_data = nullptr;
            }
            m_data = data;
        }

        template <typename T>
        typename Vector<T>::iterator Vector<T>::begin() noexcept
        {
            Vector<T>::iterator it(m_data);
            return it;
        }

        template <typename T>
        typename Vector<T>::iterator Vector<T>::end() noexcept
        {
            Vector<T>::iterator it(m_data + m_size);
            return it;
        }

        template <typename T>
        typename Vector<T>::reverse_iterator Vector<T>::rbegin() noexcept
        {
            Vector<T>::reverse_iterator it(m_data + m_size - 1);
            return it;
        }

        template <typename T>
        typename Vector<T>::reverse_iterator Vector<T>::rend() noexcept
        {
            Vector<T>::reverse_iterator it(m_data - 1);
            return it;
        }

        template <typename T>
        typename Vector<T>::iterator Vector<T>::insert(iterator pos, const T & value)
        {
            return insert(pos, 1, value);
        }

        template <typename T>
        typename Vector<T>::iterator Vector<T>::insert(iterator pos, int n, const T & value)
        {
            int size = pos - begin();
            if (m_size + n <= m_capacity)
            {
                // 数组后面那部分的元素往后挪，避免覆盖

                // 优化以后 -- start,就是把这里放了个ifelse判断
                if (is_basic_type())
                {   //这里就会直接使用移动的方法移动过去
                    std::memmove(m_data + size + n, m_data + size, (m_size - size) * sizeof(T));
                }
                else
                {
                    // 优化以前 -- start
                    for (int i = m_size; i > size; i--)
                    {
                        m_data[i + n - 1] = m_data[i - 1];//这里就会进行很多次拷贝,所以是很慢的
                    }
                    // 优化以前 -- end
                }
                // 优化以后 -- end

                // 数组中间插入的部分, 用value来填充
                for (int i = 0; i < n; i++)
                {
                    m_data[size + i] = value;
                }

                // 数组前面那部分保持不变

                m_size += n;
                return Vector<T>::iterator(m_data + size);
            }

            // 当前的数组空间不够, 需要扩容
            while (m_size + n > m_capacity)
            {
                if (m_capacity == 0)
                {
                    m_capacity = 1;
                }
                else
                {
                    m_capacity *= 2;
                }
            }

            T * data = new T[m_capacity];

            // 数组前面一部分保持不变

            // 优化以后 -- start
            if (is_basic_type())
            {
                std::memcpy(data, m_data, size * sizeof(T));
            }
            else
            {
                // 优化以前 -- start
                for (int i = 0; i < size; i++)
                {
                    data[i] = m_data[i];
                }
                // 优化以前 -- end
            }
            // 优化以后 -- end

            // 数组中间部分, 用value来填充
            for (int i = 0; i < n; i++)
            {
                data[size + i] = value;
            }

            // 数组后面那部分往后挪

            // 优化以后 -- start
            if (is_basic_type())
            {
                std::memcpy(data + size + n, m_data + size, (m_size - size) * sizeof(T));
            }
            else
            {
                // 优化以前 -- start
                for (int i = size; i < m_size; i++)
                {
                    data[i + n] = m_data[i];
                }
                // 优化以前 -- end
            }
            // 优化以后 -- end

            if (m_data != nullptr)
            {
                delete [] m_data;
                m_data = nullptr;
            }
            m_data = data;
            m_size += n;
            return Vector<T>::iterator(m_data + size);
        }

        template <typename T>
        typename Vector<T>::iterator Vector<T>::erase(iterator pos)
        {
            if (pos == end())
            {
                throw std::logic_error("out of range");
            }
            if (end() - pos == 1)
            {
                // 删除最后一个元素, 其他元素不需要移动
                m_size -= 1;
                return end();       //会返回新的尾元素指针
            }
            int size = pos - begin();

            // 优化以后 -- start
            if (is_basic_type())
            {
                std::memmove(m_data + size, m_data + size + 1, (m_size - size - 1) * sizeof(T));
            }
            else
            {
                // 优化以前 -- start
                for (int i = size; i < m_size - 1; i++)
                {
                    m_data[i] = m_data[i + 1];
                }
                // 优化以前 -- end
            }
            // 优化以后 -- end
            m_size -= 1;
            return pos;
        }

        template <typename T>
        typename Vector<T>::iterator Vector<T>::erase(iterator first, iterator last)
        {
            int f = first - begin(); // first 对应的数组下标
            int l = last - begin(); // last 对应的数组下标
            int n = last - first; // 删除的元素个数

            // 优化以后 -- start
            if (is_basic_type())
            {
                std::memmove(m_data + f, m_data + l, (m_size - l) * sizeof(T));
            }
            else
            {
                // 优化以前 -- start
                for (int i = 0; i < m_size - l; i++)
                {
                    m_data[f + i] = m_data[l + i];
                }
                // 优化以前 -- end
            }
            // 优化以后 -- end

            m_size -= n;
            return first;
        }

        template <typename T>
        bool Vector<T>::is_basic_type()//这个表示是否是基本类型
        {
            if (std::is_pointer<T>::value)//问是不是指针,指针也是基本类型
            {
                return true;
            }
            return (typeid(T) == typeid(bool)) ||
                   (typeid(T) == typeid(char)) ||
                   (typeid(T) == typeid(unsigned char)) ||
                   (typeid(T) == typeid(short)) ||
                   (typeid(T) == typeid(unsigned short)) ||
                   (typeid(T) == typeid(int)) ||
                   (typeid(T) == typeid(unsigned int)) ||
                   (typeid(T) == typeid(long)) ||
                   (typeid(T) == typeid(unsigned long)) ||
                   (typeid(T) == typeid(float)) ||
                   (typeid(T) == typeid(double));
        }
    }
}
