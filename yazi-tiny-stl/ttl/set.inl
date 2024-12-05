template <typename T, typename Container>
Set<T, Container>::Set()
{
}

template <typename T, typename Container>
Set<T, Container>::~Set()
{
    m_container.clear();
}

template <typename T, typename Container>
int Set<T, Container>::size() const
{
    return m_container.size();
}

template <typename T, typename Container>
int Set<T, Container>::count(const T & key) const
{
    auto exists = m_container.search(key);
    return exists ? 1 : 0;
}

template <typename T, typename Container>
bool Set<T, Container>::empty() const
{
    return m_container.empty();
}

template <typename T, typename Container>
void Set<T, Container>::clear()
{
    m_container.clear();
}

template <typename T, typename Container>
void Set<T, Container>::insert(const T & key)
{
    m_container.insert(key);
}

template <typename T, typename Container>
void Set<T, Container>::remove(const T & key)
{
    m_container.remove(key);
}

template <typename T, typename Container>
void Set<T, Container>::swap(Set<T, Container> & other)
{
    m_container.swap(other.m_container);
}

template <typename T, typename Container>
typename Set<T, Container>::iterator Set<T, Container>::begin()
{
    return m_container.begin();
}

template <typename T, typename Container>
typename Set<T, Container>::iterator Set<T, Container>::end()
{
    return m_container.end();
}

template <typename T, typename Container>
typename Set<T, Container>::iterator Set<T, Container>::find(const T & key)
{
    return m_container.find(key);
}

template <typename T, typename Container>
typename Set<T, Container>::const_iterator Set<T, Container>::cbegin() const
{
    return m_container.cbegin();
}

template <typename T, typename Container>
typename Set<T, Container>::const_iterator Set<T, Container>::cend() const
{
    return m_container.cend();
}

template <typename T, typename Container>
typename Set<T, Container>::const_iterator Set<T, Container>::find(const T & key) const
{
    return m_container.find();
}

template <typename T, typename Container>
typename Set<T, Container>::reverse_iterator Set<T, Container>::rbegin()
{
    return m_container.rbegin();
}

template <typename T, typename Container>
typename Set<T, Container>::reverse_iterator Set<T, Container>::rend()
{
    return m_container.rend();
}

template <typename T, typename Container>
typename Set<T, Container>::reverse_iterator Set<T, Container>::rfind(const T & key)
{
    return m_container.rfind(key);
}