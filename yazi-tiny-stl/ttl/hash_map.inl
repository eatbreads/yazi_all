template <typename K, typename V, typename Hash, typename Container>
HashMap<K, V, Hash, Container>::HashMap()
{
}

template <typename K, typename V, typename Hash, typename Container>
HashMap<K, V, Hash, Container>::~HashMap()
{
}

template <typename K, typename V, typename Hash, typename Container>
bool HashMap<K, V, Hash, Container>::insert(const Pair<K, V> & pair)
{
    return m_container.insert(pair);
}

template <typename K, typename V, typename Hash, typename Container>
bool HashMap<K, V, Hash, Container>::remove(const K & key)
{
    return m_container.remove(Pair<K, V>(key, V()));
}

template <typename K, typename V, typename Hash, typename Container>
bool HashMap<K, V, Hash, Container>::search(const K & key)
{
    return m_container.search(Pair<K, V>(key, V()));
}

template <typename K, typename V, typename Hash, typename Container>
bool HashMap<K, V, Hash, Container>::empty() const
{
    return m_container.empty();
}

template <typename K, typename V, typename Hash, typename Container>
int HashMap<K, V, Hash, Container>::size() const
{
    return m_container.size();
}

template <typename K, typename V, typename Hash, typename Container>
V & HashMap<K, V, Hash, Container>::at(const K & key)
{
    auto it = find(key);
    if (it == end())
        throw std::out_of_range("out of range");
    return it->second;
}

template <typename K, typename V, typename Hash, typename Container>
const V & HashMap<K, V, Hash, Container>::at(const K & key) const
{
    auto it = find(key);
    if (it == cend())
        throw std::out_of_range("out of range");
    return it->second;
}

template <typename K, typename V, typename Hash, typename Container>
int HashMap<K, V, Hash, Container>::bucket(const K & key) const
{
    return m_container.bucket(Pair<K, V>(key, V()));
}

template <typename K, typename V, typename Hash, typename Container>
int HashMap<K, V, Hash, Container>::bucket_count() const
{
    return m_container.bucket_count();
}

template <typename K, typename V, typename Hash, typename Container>
int HashMap<K, V, Hash, Container>::bucket_size(int slot) const
{
    return m_container.bucket_size();
}

template <typename K, typename V, typename Hash, typename Container>
int HashMap<K, V, Hash, Container>::count(const K & key) const
{
    return m_container.count(Pair<K, V>(key, V()));
}

template <typename K, typename V, typename Hash, typename Container>
float HashMap<K, V, Hash, Container>::load_factor() const
{
    return m_container.load_factory();
}

template <typename K, typename V, typename Hash, typename Container>
float HashMap<K, V, Hash, Container>::max_load_factor() const
{
    return m_container.max_load_factory();
}

template <typename K, typename V, typename Hash, typename Container>
void HashMap<K, V, Hash, Container>::max_load_factor(float f)
{
    m_container.max_load_factory(f);
}

template <typename K, typename V, typename Hash, typename Container>
Hash HashMap<K, V, Hash, Container>::hash_function() const
{
    return m_container.hash_function();
}

template <typename K, typename V, typename Hash, typename Container>
void HashMap<K, V, Hash, Container>::rehash(int n)
{
    return m_container.rehash(n);
}

template <typename K, typename V, typename Hash, typename Container>
void HashMap<K, V, Hash, Container>::clear()
{
    m_container.clear();
}

template <typename K, typename V, typename Hash, typename Container>
void HashMap<K, V, Hash, Container>::swap(HashMap<K, V, Hash, Container> & other)
{
    m_container.swap(other.m_container);
}

template <typename K, typename V, typename Hash, typename Container>
void HashMap<K, V, Hash, Container>::show() const
{
    m_container.show();
}

template <typename K, typename V, typename Hash, typename Container>
typename HashMap<K, V, Hash, Container>::iterator HashMap<K, V, Hash, Container>::begin()
{
    return m_container.begin();
}

template <typename K, typename V, typename Hash, typename Container>
typename HashMap<K, V, Hash, Container>::iterator HashMap<K, V, Hash, Container>::end()
{
    return m_container.end();
}

template <typename K, typename V, typename Hash, typename Container>
typename HashMap<K, V, Hash, Container>::iterator HashMap<K, V, Hash, Container>::find(const K & key)
{
    return m_container.find(Pair<K, V>(key, V()));
}

template <typename K, typename V, typename Hash, typename Container>
typename HashMap<K, V, Hash, Container>::const_iterator HashMap<K, V, Hash, Container>::cbegin() const
{
    return m_container.cbegin();
}

template <typename K, typename V, typename Hash, typename Container>
typename HashMap<K, V, Hash, Container>::const_iterator HashMap<K, V, Hash, Container>::cend() const
{
    return m_container.cend();
}

template <typename K, typename V, typename Hash, typename Container>
typename HashMap<K, V, Hash, Container>::const_iterator HashMap<K, V, Hash, Container>::find(const K & key) const
{
    return m_container.find(Pair<K, V>(key, V()));
}

template <typename K, typename V, typename Hash, typename Container>
V & HashMap<K, V, Hash, Container>::operator [] (const K & key)
{
    auto it = m_container.find(Pair<K, V>(key, V()));
    if (it == end())
    {
        m_container.insert(Pair<K, V>(key, V()));
        it = m_container.find(Pair<K, V>(key, V()));
    }
    return it->second;
}
