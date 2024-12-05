template <typename T, typename Hash, typename Container>
HashSet<T, Hash, Container>::HashSet()
{
}

template <typename T, typename Hash, typename Container>
HashSet<T, Hash, Container>::~HashSet()
{
}

template <typename T, typename Hash, typename Container>
bool HashSet<T, Hash, Container>::insert(const T & key)
{
    return m_container.insert(key);
}

template <typename T, typename Hash, typename Container>
bool HashSet<T, Hash, Container>::remove(const T & key)
{
    return m_container.remove(key);
}

template <typename T, typename Hash, typename Container>
bool HashSet<T, Hash, Container>::search(const T & key)
{
    return m_container.search(key);
}

template <typename T, typename Hash, typename Container>
bool HashSet<T, Hash, Container>::empty() const
{
    return m_container.empty();
}

template <typename T, typename Hash, typename Container>
int HashSet<T, Hash, Container>::size() const
{
    return m_container.size();
}

template <typename T, typename Hash, typename Container>
int HashSet<T, Hash, Container>::bucket(const T & key) const
{
    return m_container.bucket(key);
}

template <typename T, typename Hash, typename Container>
int HashSet<T, Hash, Container>::bucket_count() const
{
    return m_container.bucket_count();
}

template <typename T, typename Hash, typename Container>
int HashSet<T, Hash, Container>::bucket_size(int slot) const
{
    return m_container.bucket_size();
}

template <typename T, typename Hash, typename Container>
int HashSet<T, Hash, Container>::count(const T & key) const
{
    return m_container.count(key);
}

template <typename T, typename Hash, typename Container>
float HashSet<T, Hash, Container>::load_factor() const
{
    return m_container.load_factory();
}

template <typename T, typename Hash, typename Container>
float HashSet<T, Hash, Container>::max_load_factor() const
{
    return m_container.max_load_factory();
}

template <typename T, typename Hash, typename Container>
void HashSet<T, Hash, Container>::max_load_factor(float f)
{
    m_container.max_load_factory(f);
}

template <typename T, typename Hash, typename Container>
Hash HashSet<T, Hash, Container>::hash_function() const
{
    return m_container.hash_function();
}

template <typename T, typename Hash, typename Container>
void HashSet<T, Hash, Container>::rehash(int n)
{
    return m_container.rehash(n);
}

template <typename T, typename Hash, typename Container>
void HashSet<T, Hash, Container>::clear()
{
    m_container.clear();
}

template <typename T, typename Hash, typename Container>
void HashSet<T, Hash, Container>::swap(HashSet<T, Hash, Container> & other)
{
    m_container.swap(other.m_container);
}

template <typename T, typename Hash, typename Container>
void HashSet<T, Hash, Container>::show() const
{
    m_container.show();
}

template <typename T, typename Hash, typename Container>
typename HashSet<T, Hash, Container>::iterator HashSet<T, Hash, Container>::begin()
{
    return m_container.begin();
}

template <typename T, typename Hash, typename Container>
typename HashSet<T, Hash, Container>::iterator HashSet<T, Hash, Container>::end()
{
    return m_container.end();
}

template <typename T, typename Hash, typename Container>
typename HashSet<T, Hash, Container>::iterator HashSet<T, Hash, Container>::find(const T & key)
{
    return m_container.find(key);
}

template <typename T, typename Hash, typename Container>
typename HashSet<T, Hash, Container>::const_iterator HashSet<T, Hash, Container>::cbegin() const
{
    return m_container.cbegin();
}

template <typename T, typename Hash, typename Container>
typename HashSet<T, Hash, Container>::const_iterator HashSet<T, Hash, Container>::cend() const
{
    return m_container.cend();
}

template <typename T, typename Hash, typename Container>
typename HashSet<T, Hash, Container>::const_iterator HashSet<T, Hash, Container>::find(const T & key) const
{
    return m_container.find(key);
}
