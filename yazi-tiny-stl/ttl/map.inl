template <typename K, typename V, typename Container>
Map<K, V, Container>::Map()
{
}

template <typename K, typename V, typename Container>
Map<K, V, Container>::~Map()
{
    m_container.clear();
}

template <typename K, typename V, typename Container>
int Map<K, V, Container>::size() const
{
    return m_container.size();
}

template <typename K, typename V, typename Container>
int Map<K, V, Container>::count(const K & key) const
{
    auto exists = m_container.search(Pair<K, V>(key, V()));
    return exists ? 1 : 0;
}

template <typename K, typename V, typename Container>
bool Map<K, V, Container>::empty() const
{
    return m_container.empty();
}

template <typename K, typename V, typename Container>
void Map<K, V, Container>::clear()
{
    m_container.clear();
}

template <typename K, typename V, typename Container>
void Map<K, V, Container>::insert(const Pair<K, V> & pair)
{
    m_container.insert(pair);
}

template <typename K, typename V, typename Container>
void Map<K, V, Container>::remove(const K & key)
{
    m_container.remove(Pair<K, V>(key, V()));
}

template <typename K, typename V, typename Container>
V & Map<K, V, Container>::at(const K & key)
{
    auto it = m_container.find(Pair<K, V>(key, V()));
    if (it == end())
        throw std::out_of_range("out of range");
    return it->second;
}

template <typename K, typename V, typename Container>
const V & Map<K, V, Container>::at(const K & key) const
{
    auto it = m_container.find(Pair<K, V>(key, V()));
    if (it == cend())
        throw std::out_of_range("out of range");
    return it->second;
}

template <typename K, typename V, typename Container>
void Map<K, V, Container>::swap(Map<K, V, Container> & other)
{
    m_container.swap(other.m_container);
}

template <typename K, typename V, typename Container>
typename Map<K, V, Container>::iterator Map<K, V, Container>::begin()
{
    return m_container.begin();
}

template <typename K, typename V, typename Container>
typename Map<K, V, Container>::iterator Map<K, V, Container>::end()
{
    return m_container.end();
}

template <typename K, typename V, typename Container>
typename Map<K, V, Container>::iterator Map<K, V, Container>::find(const K & key)
{
    return m_container.find(Pair<K, V>(key, V()));
}

template <typename K, typename V, typename Container>
typename Map<K, V, Container>::const_iterator Map<K, V, Container>::cbegin() const
{
    return m_container.cbegin();
}

template <typename K, typename V, typename Container>
typename Map<K, V, Container>::const_iterator Map<K, V, Container>::cend() const
{
    return m_container.cend();
}

template <typename K, typename V, typename Container>
typename Map<K, V, Container>::const_iterator Map<K, V, Container>::find(const K & key) const
{
    return m_container.find(Pair<K, V>(key, V()));
}

template <typename K, typename V, typename Container>
typename Map<K, V, Container>::reverse_iterator Map<K, V, Container>::rbegin()
{
    return m_container.rbegin();
}

template <typename K, typename V, typename Container>
typename Map<K, V, Container>::reverse_iterator Map<K, V, Container>::rend()
{
    return m_container.rend();
}

template <typename K, typename V, typename Container>
typename Map<K, V, Container>::reverse_iterator Map<K, V, Container>::rfind(const K & key)
{
    return m_container.rfind(Pair<K, V>(key, V()));
}

template <typename K, typename V, typename Container>
V & Map<K, V, Container>::operator [] (const K & key)
{
    auto it = m_container.find(Pair<K, V>(key, V()));
    if (it == end())
    {
        m_container.insert(Pair<K, V>(key, V()));
        it = m_container.find(Pair<K, V>(key, V()));
    }
    return it->second;
}
