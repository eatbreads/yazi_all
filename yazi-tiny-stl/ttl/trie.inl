template <typename T>
Trie<T>::Trie() : m_root(nullptr), m_size(0)
{
    m_root = new Node();
}

template <typename T>
Trie<T>::~Trie()
{
    if (m_root != nullptr)
    {
        delete m_root;
        m_root = nullptr;
    }
}

template <>
void Trie<string>::insert(const string & key)
{
    insert(key.data(), key.size());
}

template <typename T>
void Trie<T>::insert(const T & key)
{
    std::string str = std::to_string(key);
    insert(str.data(), str.size());
}

template <typename T>
void Trie<T>::insert(const char * data, int size)
{
    auto node = m_root;
    for (int i = 0; i < size; i++)
    {
        int idx;
        bool found = false;
        for (idx = 0; idx < node->m_size; idx++)
        {
            if (data[i] == node->m_children[idx]->m_data)
            {
                found = true;
                break;
            }
            else if (data[i] < node->m_children[idx]->m_data)
            {
                break;
            }
        }
        if (found)
        {
            node = node->m_children[idx];
            if (i == size - 1)
                node->m_flag = true;
        }
        else
        {
            auto child = new Node();
            child->m_data = data[i];
            child->m_flag = (i == size - 1);
            node->insert(idx, child);
            node = child;
        }
    }
    m_size += 1;
}

template <>
bool Trie<string>::search(const string & key)
{
    auto node = search(key.data(), key.size());
    if (!node)
        return false;
    return node->m_flag;
}

template <typename T>
bool Trie<T>::search(const T & key)
{
    string str = std::to_string(key);
    auto node = search(str.data(), str.size());
    if (!node)
        return false;
    return node->m_flag;
}

template <typename T>
typename Trie<T>::Node * Trie<T>::search(const char * data, int size)
{
    auto node = m_root;
    for (int i = 0; i < size; i++)
    {
        int idx;
        bool found = false;
        for (idx = 0; idx < node->m_size; idx++)
        {
            if (data[i] == node->m_children[idx]->m_data)
            {
                found = true;
                break;
            }
            else if (data[i] < node->m_children[idx]->m_data)
            {
                break;
            }
        }
        if (!found)
            return nullptr;
        node = node->m_children[idx];
    }
    return node;
}

template <>
bool Trie<string>::prefix(const string & key)
{
    auto node = search(key.data(), key.size());
    return node != nullptr;
}

template <typename T>
bool Trie<T>::prefix(const T & key)
{
    string str = std::to_string(key);
    auto node = search(str.data(), str.size());
    return node != nullptr;
}

template <>
void Trie<string>::remove(const string & key)
{
    return remove(key.data(), key.size());
}

template <typename T>
void Trie<T>::remove(const T & key)
{
    string str = std::to_string(key);
    return remove(str.data(), str.size());
}

template <typename T>
void Trie<T>::remove(const char * data, int size)
{
    auto node = m_root;
    Node * last_branch_node = nullptr;
    int last_branch_idx = 0;
    for (int i = 0; i < size; i++)
    {
        int idx;
        bool found = false;
        for (idx = 0; idx < node->m_size; idx++)
        {
            if (data[i] == node->m_children[idx]->m_data)
            {
                found = true;
                break;
            }
            else if (data[i] < node->m_children[idx]->m_data)
            {
                break;
            }
        }
        if (!found)
            return;
        if (node->m_size > 1)
        {
            last_branch_node = node;
            last_branch_idx = idx;
        }
        node = node->m_children[idx];
    }

    if (node->m_size > 0)
    {
        // case 1
        node->m_flag = false;
        return;
    }

    if (last_branch_node != nullptr)
    {
        // case 2
        last_branch_node->remove(last_branch_idx);
    }
    else
    {
        // case 3
        m_root->remove(last_branch_idx);
    }
}

template <typename T>
int Trie<T>::size() const
{
    return m_size;
}

template <typename T>
bool Trie<T>::empty() const
{
    return m_size == 0;
}

template <typename T>
void Trie<T>::clear()
{
    if (m_root != nullptr)
    {
        delete m_root;
        m_root = nullptr;
    }
}

template <typename T>
void Trie<T>::swap(Trie<T> & other)
{
    auto root = other.m_root;
    other.m_root = m_root;
    m_root = root;
}

template <typename T>
typename Trie<T>::iterator Trie<T>::begin()
{
    if (m_root == nullptr)
        return end();
    iterator it(m_root);
    ++it;
    return it;
}

template <typename T>
typename Trie<T>::iterator Trie<T>::end()
{
    return iterator(m_root);
}

template <typename T>
typename Trie<T>::iterator Trie<T>::find(const T & key)
{
    TrieStack stack;
    std::string str = std::to_string(key);
    bool found = find(str.data(), str.size(), stack);
    if (!found)
        return end();
    return iterator(m_root, stack);
}

template <>
typename Trie<string>::iterator Trie<string>::find(const string & key)
{
    TrieStack stack;
    bool found = find(key.data(), key.size(), stack);
    if (!found)
        return end();
    return iterator(m_root, stack);
}

template <typename T>
bool Trie<T>::find(const char * data, int size, TrieStack & stack) const
{
    auto node = m_root;
    for (int i = 0; i < size; i++)
    {
        int idx;
        bool found = false;
        for (idx = 0; idx < node->m_size; idx++)
        {
            if (data[i] == node->m_children[idx]->m_data)
            {
                found = true;
                stack.push_back(std::pair<Node *, int>(node, idx));
                break;
            }
            else if (data[i] < node->m_children[idx]->m_data)
            {
                break;
            }
        }
        if (!found)
            return false;
        node = node->m_children[idx];
    }
    return true;
}

template <typename T>
typename Trie<T>::const_iterator Trie<T>::cbegin() const
{
    if (m_root == nullptr)
        return cend();
    const_iterator it(m_root);
    ++it;
    return it;
}

template <typename T>
typename Trie<T>::const_iterator Trie<T>::cend() const
{
    return const_iterator(m_root);
}

template <typename T>
typename Trie<T>::const_iterator Trie<T>::find(const T & key) const
{
    TrieStack stack;
    std::string str = std::to_string(key);
    bool found = find(str.data(), str.size(), stack);
    if (!found)
        return cend();
    return const_iterator(m_root, stack);
}

template <>
typename Trie<string>::const_iterator Trie<string>::find(const string & key) const
{
    TrieStack stack;
    bool found = find(key.data(), key.size(), stack);
    if (!found)
        return cend();
    return const_iterator(m_root, stack);
}

template <typename T>
typename Trie<T>::reverse_iterator Trie<T>::rbegin()
{
    if (m_root == nullptr)
        return rend();
    reverse_iterator it(m_root);
    ++it;
    return it;
}

template <typename T>
typename Trie<T>::reverse_iterator Trie<T>::rend()
{
    return reverse_iterator(m_root);
}

template <typename T>
typename Trie<T>::reverse_iterator Trie<T>::rfind(const T & key)
{
    TrieStack stack;
    string str = std::to_string(key);
    bool found = find(str.data(), str.size(), stack);
    if (!found)
        return rend();
    return reverse_iterator(m_root, stack);
}

template <>
typename Trie<string>::reverse_iterator Trie<string>::rfind(const string & key)
{
    TrieStack stack;
    bool found = find(key.data(), key.size(), stack);
    if (!found)
        return rend();
    return reverse_iterator(m_root, stack);
}
