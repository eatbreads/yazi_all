template <typename T, typename Container>
Queue<T, Container>::Queue() {}

template <typename T, typename Container>
Queue<T, Container>::~Queue() {}

template <typename T, typename Container>
void Queue<T, Container>::push(const T & value)
{
    m_container.push_back(value);
}

template <typename T, typename Container>
void Queue<T, Container>::pop()
{
    m_container.pop_front();
}

template <typename T, typename Container>
T & Queue<T, Container>::front()
{
    return m_container.front();
}

template <typename T, typename Container>
const T & Queue<T, Container>::front() const
{
    return m_container.front();
}

template <typename T, typename Container>
T & Queue<T, Container>::back()
{
    return m_container.back();
}

template <typename T, typename Container>
const T & Queue<T, Container>::back() const
{
    return m_container.back();
}

template <typename T, typename Container>
int Queue<T, Container>::size() const
{
    return m_container.size();
}

template <typename T, typename Container>
bool Queue<T, Container>::empty() const
{
    return m_container.empty();
}

template <typename T, typename Container>
void Queue<T, Container>::swap(Queue<T, Container> & other)
{
    m_container.swap(other.m_container);
}

template <typename T, typename Container>
void Queue<T, Container>::show() const
{
    m_container.show();
}
