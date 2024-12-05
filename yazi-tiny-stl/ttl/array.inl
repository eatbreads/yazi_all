template <typename T, int N>//记得每一个都要加template
Array<T, N>::Array()
{//这里仅仅只是做了初始化为空
    std::memset(m_data, 0, sizeof(T) * N);//使用了模板参数和非类型模板参数
}

template <typename T, int N>
Array<T, N>::~Array()
{ 
}

template <typename T, int N>
int Array<T, N>::size() const
{
    return N;
}

template <typename T, int N>
bool Array<T, N>::empty() const
{
    return N == 0;
}

template <typename T, int N>
void Array<T, N>::show() const
{
    std::cout << "size = " << size() << std::endl;
    for (int i = 0; i < N; i++)
    {
        std::cout << m_data[i] << ", ";
    }
    std::cout << std::endl;
}

template <typename T, int N>
T * Array<T, N>::data()
{
    return m_data;
}

template <typename T, int N>
const T * Array<T, N>::data() const
{
    return m_data;
}

template <typename T, int N>
void Array<T, N>::swap(Array<T, N> & other)
{
    if (this == &other)
    {
        return;
    }
    for (int i = 0; i < N; i++)
    {
        auto temp = other.m_data[i];
        other.m_data[i] = m_data[i];
        m_data[i] = temp;
    }
}

template <typename T, int N>
void Array<T, N>::fill(const T & value)//这边表示把所有空间都填充为这个value
{
    for (int i = 0; i < N; i++)
    {
        m_data[i] = value;
    }
}

template <typename T, int N>
T & Array<T, N>::front()
{
    return m_data[0];
}

template <typename T, int N>
const T & Array<T, N>::front() const
{
    return m_data[0];
}

template <typename T, int N>
T & Array<T, N>::back()
{
    return m_data[N - 1];
}

template <typename T, int N>
const T & Array<T, N>::back() const
{
    return m_data[N - 1];
}

template <typename T, int N>
T & Array<T, N>::at(int index)
{
    if (index < 0 || index >= N)
    {
        throw std::out_of_range("out of range");
    }
    return m_data[index];
}

template <typename T, int N>
const T & Array<T, N>::at(int index) const
{
    if (index < 0 || index >= N)
    {
        throw std::out_of_range("out of range");
    }
    return m_data[index];
}

template <typename T, int N>
T & Array<T, N>::operator [] (int index)
{
    return m_data[index];
}

template <typename T, int N>
const T & Array<T, N>::operator [] (int index) const
{
    return m_data[index];
}

template <typename T, int N>
typename Array<T, N>::iterator Array<T, N>::begin()//这个写法还挺难,这是返回里面的一个别名
{
    return iterator(m_data);
}

template <typename T, int N>
typename Array<T, N>::iterator Array<T, N>::end()
{ 
    return iterator(m_data + N);
}

template <typename T, int N>
typename Array<T, N>::const_iterator Array<T, N>::cbegin() const
{
    return const_iterator((T *)m_data);//为什么这里要强转,他作为数组首地址不就本身就是T*吗
                                        //这边不是很懂,但是不强转编译器会报错
}

template <typename T, int N>
typename Array<T, N>::const_iterator Array<T, N>::cend() const
{
    return const_iterator((T *)m_data + N);
}

template <typename T, int N>
typename Array<T, N>::reverse_iterator Array<T, N>::rbegin()
{
    return reverse_iterator(m_data + N - 1);
}

template <typename T, int N>
typename Array<T, N>::reverse_iterator Array<T, N>::rend()
{
    return reverse_iterator(m_data - 1);
}