template <typename T>
Vector<T>::Vector() : m_data(nullptr), m_size(0), m_capacity(0)
{
}

template <typename T>
Vector<T>::Vector(const Vector<T> & other)
{
    *this = other;
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
void Vector<T>::assign(int n, const T & value)
{
    if (m_capacity >= n)
    {
        for (int i = 0; i < n; i++)
        {
            m_data[i] = value;
        }
        m_size = n;
        return;
    }
    if (m_data != nullptr)
    {
        delete m_data;
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
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
    m_data = new T[m_capacity];
    for (int i = 0; i < n; i++)
    {
        m_data[i] = value;
    }
    m_size = n;
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
        std::cout << m_data[i] << ", ";
    }
    std::cout << std::endl;
}

template <typename T>
T & Vector<T>::at(int index)
{
    if (index < 0 || index >= m_size)
    {
        throw std::out_of_range("out of range");
    }
    return m_data[index];
}

template <typename T>
const T & Vector<T>::at(int index) const
{
    if (index < 0 || index >= m_size)
    {
        throw std::out_of_range("out of range");
    }
    return m_data[index];
}

template <typename T>
T & Vector<T>::front()
{
    return m_data[0];
}

template <typename T>
const T & Vector<T>::front() const
{
    return m_data[0];
}

template <typename T>
T & Vector<T>::back()
{
    return m_data[m_size - 1];
}

template <typename T>
const T & Vector<T>::back() const
{
    return m_data[m_size - 1];
}

template <typename T>
bool Vector<T>::empty() const
{
    return m_size == 0;
}

template <typename T>
void Vector<T>::clear()
{
    m_size = 0;
}

template <typename T>
int Vector<T>::size() const
{
    return m_size;
}

template <typename T>
int Vector<T>::capacity() const
{
    return m_capacity;
}

template <typename T>
T * Vector<T>::data()
{
    return m_data;
}

template <typename T>
const T * Vector<T>::data() const
{
    return m_data;
}

template <typename T>
T & Vector<T>::operator [] (int index)
{
    return m_data[index];
}

template <typename T>
const T & Vector<T>::operator [] (int index) const
{
    return m_data[index];
}

template <typename T>
Vector<T> & Vector<T>::operator = (const Vector<T> & other)
{
    if (this == &other)
    {
        return *this;
    }
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
    if (this == &other)
    {
        return;
    }
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
    resize(n, T());
}

template <typename T>
void Vector<T>::resize(int n, const T & value)
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
    if (m_data != nullptr)
    {
        delete [] m_data;
        m_data = nullptr;
    }
    m_data = data;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return iterator(m_data);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end()
{
    return iterator(m_data + m_size);
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

        // 优化以后 -- start
        if (is_basic_type())
        {
            std::memmove(m_data + size + n, m_data + size, (m_size - size) * sizeof(T));
        }
        else
        {
            // 优化以前 -- start
            for (int i = m_size; i > size; i--)
            {
                m_data[i + n - 1] = m_data[i - 1];
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
        return iterator(m_data + size);
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
    return iterator(m_data + size);
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
        return end();
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
typename Vector<T>::const_iterator Vector<T>::cbegin() const
{
    return const_iterator(m_data);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const
{
    return const_iterator(m_data + m_size);
}

template <typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin()
{
    return reverse_iterator(m_data + m_size - 1);
}

template <typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend()
{
    return reverse_iterator(m_data - 1);
}

template <typename T>
bool Vector<T>::is_basic_type()
{
    if (std::is_pointer<T>::value)
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