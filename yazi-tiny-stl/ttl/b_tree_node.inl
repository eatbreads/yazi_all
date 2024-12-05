template <typename T, int t>
BTreeNode<T, t>::BTreeNode(Node * parent, bool leaf) : m_parent(parent), m_leaf(leaf)
{
    m_keys = new T[2 * t - 1];
    std::memset(m_keys, 0, sizeof(T) * (2 * t - 1));
    if (!m_leaf)
    {
        m_children = new Node *[2 * t];
        std::memset(m_children, 0, sizeof(Node *) * 2 * t);
    }
    else
    {
        m_children = nullptr;
    }
    m_size = 0;
    m_index = 0;
}

template <typename T, int t>
BTreeNode<T, t>::~BTreeNode()
{
    delete [] m_keys;
    if (!m_leaf)
    {
        delete [] m_children;
    }
}

template <typename T, int t>
typename BTreeNode<T, t>::Node * BTreeNode<T, t>::leftmost()
{
    auto node = this;
    while (!node->m_leaf)
        node = node->m_children[0];
    return node;
}

template <typename T, int t>
typename BTreeNode<T, t>::Node * BTreeNode<T, t>::rightmost()
{
    auto node = this;
    while (!node->m_leaf)
        node = node->m_children[node->m_size];
    return node;
}

template <typename T, int t>
void BTreeNode<T, t>::take_from_left()
{
    if (m_index == 0)
        throw std::logic_error("shift from left error: sibling is null");

    auto sibling = m_parent->m_children[m_index - 1];
    for (int i = m_size; i > 0; i--)
    {
        m_keys[i] = m_keys[i - 1];
    }
    m_keys[0] = m_parent->m_keys[m_index - 1];
    m_parent->m_keys[m_index - 1] = sibling->m_keys[sibling->m_size - 1];
    if (!m_leaf)
    {
        for (int i = m_size; i >= 0; i--)
        {
            m_children[i + 1] = m_children[i];
            m_children[i + 1]->m_index = i + 1;
        }
        auto child = sibling->m_children[sibling->m_size];
        child->m_parent = this;
        child->m_index = 0;
        m_children[0] = child;
    }
    m_size++;
    sibling->m_size--;
}

template <typename T, int t>
void BTreeNode<T, t>::take_from_right()
{
    if (m_index == m_parent->m_size)
        throw std::logic_error("shift from right error: sibling is null");

    auto sibling = m_parent->m_children[m_index + 1];
    m_keys[m_size] = m_parent->m_keys[m_index];
    m_parent->m_keys[m_index] = sibling->m_keys[0];
    for (int i = 0; i < sibling->m_size - 1; i++)
    {
        sibling->m_keys[i] = sibling->m_keys[i + 1];
    }
    if (!m_leaf)
    {
        auto child = sibling->m_children[0];
        child->m_parent = this;
        child->m_index = m_size + 1;
        m_children[m_size + 1] = child;
        for (int i = 0; i < sibling->m_size; i++)
        {
            sibling->m_children[i] = sibling->m_children[i + 1];
            sibling->m_children[i]->m_index = i;
        }
    }
    m_size++;
    sibling->m_size--;
}

template <typename T, int t>
void BTreeNode<T, t>::insert(const T & key)
{
    if (m_leaf)
    {
        int i = m_size - 1;
        while (i >= 0 && m_keys[i] > key)
        {
            m_keys[i + 1] = m_keys[i];
            i--;
        }
        m_keys[i + 1] = key;
        m_size++;
    }
    else
    {
        int i = 0;
        while (i < m_size && key > m_keys[i])
            i++;
        if (m_children[i]->full())
        {
            split(i);
            if (m_keys[i] < key)
                i++;
        }
        m_children[i]->insert(key);
    }
}

template <typename T, int t>
typename BTreeNode<T, t>::Node * BTreeNode<T, t>::search(const T & key)
{
    int i = 0;
    while (i < m_size && key > m_keys[i])
        i++;
    if (m_keys[i] == key)
        return this;
    if (m_leaf)
        return nullptr;
    return m_children[i]->search(key);
}

template <typename T, int t>
bool BTreeNode<T, t>::thin() const
{
    return m_size == t - 1;
}

template <typename T, int t>
bool BTreeNode<T, t>::full() const
{
    return m_size == 2 * t - 1;
}

template <typename T, int t>
bool BTreeNode<T, t>::empty() const
{
    return m_size == 0;
}

template <typename T, int t>
void BTreeNode<T, t>::show() const
{
    std::cout << "keys[" << m_size << "] = [";
    for (int i = 0; i < m_size; i++)
    {
        if (i != 0)
            std::cout << ", ";
        std::cout << m_keys[i];
    }
    std::cout << "]";
}

template <typename T, int t>
void BTreeNode<T, t>::split(int i)
{
    // child will be spilt into two node
    auto child = m_children[i];
    auto node = new Node(this, child->m_leaf);

    // copy the last (t-1) keys of child to node
    for (int k = 0; k < t - 1; k++)
    {
        node->m_keys[k] = child->m_keys[k + t];
    }
    node->m_size = t - 1;

    // copy the last t children of child to node
    if (!child->m_leaf)
    {
        for (int k = 0; k < t; k++)
        {
            auto c = child->m_children[k + t];
            node->m_children[k] = c;
            c->m_index = k;
            c->m_parent = node;
        }
    }

    /*
     * 备注:
     * 一个满的节点一共有2t-1个key，split分裂的时候，会分成左右两个节点
     * 这两个节点的key数量一样多，都是 t-1。另外还有一个多余的 key 会溢出到父节点
     * 2t-1 = (t-1) + (t-1) + 1
     */
    child->m_size = t - 1;

    /*
     * 这个就是多余的 key, 会溢出到父节点
     * 当前节点就是 child 的父节点
     * 所以 child 节点分裂以后溢出的 key 就由当前节点接收
     */
    T key = child->m_keys[t - 1];

    /*
     * 当前节点为了接收这个溢出的 key 会做两点调整
     * 1: keys数组会挪出一个位置给这个 key
     * 2: children数组挪出一个位置给扩容以后的新节点
     */
    // keys数组会挪出一个位置给这个 key
    for (int k = m_size - 1; k >= i; k--)
        m_keys[k + 1] = m_keys[k];
    m_keys[i] = key;

    // children数组挪出一个位置给扩容以后的新节点
    for (int k = m_size; k >= i + 1; k--)
    {
        auto c = m_children[k];
        m_children[k + 1] = c;
        c->m_index = k + 1;
    }
    m_children[i + 1] = node;
    m_children[i + 1]->m_index = i + 1;

    // resize number of keys;
    m_size++;
}

template <typename T, int t>
void BTreeNode<T, t>::merge(int i)
{
    if (m_leaf)
        return;
    auto child = m_children[i];
    auto sibling = m_children[i + 1];
    if (!(child->thin() && sibling->thin()))
        return;

    // move one parent key into child
    child->m_keys[t - 1] = m_keys[i];

    // move all sibling keys into child
    for (int k = 0; k < sibling->m_size; k++)
    {
        child->m_keys[t + k] = sibling->m_keys[k];
    }

    if (!child->m_leaf)
    {
        // move all sibling children into child
        for (int k = 0; k <= sibling->m_size; k++)
        {
            auto c = sibling->m_children[k];
            child->m_children[t + k] = c;
            c->m_parent = child;
            c->m_index = t + k;
        }
    }

    // shift all keys to left by one
    for (int k = i + 1; k < m_size; k++)
        m_keys[k - 1] = m_keys[k];

    // shift all children to left by one
    for (int k = i + 2; k <= m_size; k++)
    {
        m_children[k - 1] = m_children[k];
        m_children[k - 1]->m_index = k - 1;
    }

    m_size--;
    child->m_size = 2 * t - 1;
    delete sibling;
}

template <typename T, int t>
void BTreeNode<T, t>::fill(int i)
{
    if (i > 0 && m_children[i - 1]->m_size >= t)
    {
        m_children[i]->take_from_left();
    }
    else if (i < m_size && m_children[i + 1]->m_size >= t)
    {
        m_children[i]->take_from_right();
    }
    else
    {
        if (i != m_size)
            merge(i);
        else
            merge(i - 1);
    }
}

template <typename T, int t>
void BTreeNode<T, t>::traverse()
{
    int i;
    for (i = 0; i < m_size; i++)
    {
        if (!m_leaf)
            m_children[i]->traverse();
        std::cout << m_keys[i] << ", ";
    }
    if (!m_leaf)
        m_children[i]->traverse();
}

template <typename T, int t>
bool BTreeNode<T, t>::remove(const T & key)
{
    int i = 0;
    while (i < m_size && m_keys[i] < key)
        i++;
    if (i < m_size && m_keys[i] == key)
    {
        if (m_leaf)
            return remove_from_leaf(i);
        else
            return remove_from_none_leaf(i);
    }
    else
    {
        if (m_leaf)
        {
            // not found
            return false;
        }
        bool flag = (i == m_size);
        if (m_children[i]->m_size < t)
            fill(i);

        if (flag && i > m_size)
            return m_children[i - 1]->remove(key);
        else
            return m_children[i]->remove(key);
    }
}

template <typename T, int t>
bool BTreeNode<T, t>::remove_from_leaf(int i)
{
    for (int k= i + 1; k < m_size; k++)
        m_keys[k - 1] = m_keys[k];
    m_size--;
    return true;
}

template <typename T, int t>
bool BTreeNode<T, t>::remove_from_none_leaf(int i)
{
    T key = m_keys[i];
    if (m_children[i]->m_size > t - 1)
    {
        T repl = predecessor(i);
        m_keys[i] = repl;
        return m_children[i]->remove(repl);
    }
    else if (m_children[i + 1]->m_size > t - 1)
    {
        T repl = successor(i);
        m_keys[i] = repl;
        return m_children[i + 1]->remove(repl);
    }
    merge(i);
    return m_children[i]->remove(key);
}

template <typename T, int t>
T BTreeNode<T, t>::predecessor(int i)
{
    auto node = m_children[i];
    while (!node->m_leaf)
        node = node->m_children[node->m_size];
    return node->m_keys[node->m_size - 1];
}

template <typename T, int t>
T BTreeNode<T, t>::successor(int i)
{
    auto node = m_children[i + 1];
    while (!node->m_leaf)
        node = node->m_children[0];
    return node->m_keys[0];
}
