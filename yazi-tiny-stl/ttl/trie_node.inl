template <typename T>
TrieNode<T>::TrieNode() : m_data(' '), m_flag(false), m_children(nullptr), m_size(0)
{
}

template <typename T>
TrieNode<T>::~TrieNode()
{
    if (m_children != nullptr)
    {
        for (int i = 0; i < m_size; i++)
        {
            delete m_children[i];
        }
        delete [] m_children;
        m_children = nullptr;
    }
}

template <typename T>
void TrieNode<T>::insert(int idx, Node * child)
{
    auto children = new Node*[m_size + 1];
    for (int i = 0; i < idx; i++)
    {
        children[i] = m_children[i];
    }
    children[idx] = child;
    for (int i = idx; i < m_size; i++)
    {
        children[i + 1] = m_children[i];
    }

    if (m_children != nullptr)
    {
        delete [] m_children;
        m_children = nullptr;
    }
    m_children = children;
    m_size += 1;
}

template <typename T>
void TrieNode<T>::remove(int idx)
{
    auto child = m_children[idx];
    delete child;
    if (m_size == 1)
    {
        delete [] m_children;
        m_children = nullptr;
        m_size = 0;
        return;
    }
    auto children = new Node*[m_size - 1];
    for (int i = 0; i < idx; i++)
    {
        children[i] = m_children[i];
    }
    for (int i = idx + 1; i < m_size; i++)
    {
        children[i - 1] = m_children[i];
    }

    delete [] m_children;
    m_children = children;
    m_size -= 1;
}

template <typename T>
void TrieNode<T>::first(TrieStack & stack)
{
    auto node = this;
    while (node->m_size > 0)
    {
        stack.push_back(std::pair<Node *, int>(node, 0));
        node = node->m_children[0];
        if (node->m_flag)
            break;
    }
}

template <typename T>
void TrieNode<T>::last(TrieStack & stack)
{
    auto node = this;
    while (node->m_size > 0)
    {
        stack.push_back(std::pair<Node *, int>(node, node->m_size - 1));
        node = node->m_children[node->m_size - 1];
    }
}

template <typename T>
void TrieNode<T>::predecessor(TrieStack & stack)
{
    auto pair = stack.back();
    while (pair.second == 0)
    {
        stack.pop_back();
        if (stack.empty())
            return;
        pair = stack.back();
        auto node = pair.first;
        auto child = node->m_children[pair.second];
        if (child->m_flag)
            return;
    }
    stack.pop_back();
    auto node = pair.first;
    auto index = pair.second - 1;
    auto child = node->m_children[index];
    stack.push_back(std::pair<Node *, int>(node, index));
    child->last(stack);
}

template <typename T>
void TrieNode<T>::successor(TrieStack & stack)
{
    if (m_size > 0)
        return first(stack);

    auto pair = stack.back();
    while (pair.second == pair.first->m_size - 1)
    {
        stack.pop_back();
        if (stack.empty())
            return;
        pair = stack.back();
    }
    stack.pop_back();
    auto node = pair.first;
    auto index = pair.second + 1;
    auto child = node->m_children[index];
    stack.push_back(std::pair<Node *, int>(node, index));
    if (child->m_flag)
        return;
    child->first(stack);
}
