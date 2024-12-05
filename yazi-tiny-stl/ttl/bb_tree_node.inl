template <typename T, int t>
BBTreeNode<T, t>::BBTreeNode(Node * parent, bool leaf) : m_parent(parent), m_leaf(leaf)
{
    m_keys = new T[2 * t - 1];
    std::memset(m_keys, 0, sizeof(T) * (2 * t - 1));
    m_size = 0;
    m_index = 0;
}

template <typename T, int t>
BBTreeNode<T, t>::~BBTreeNode()
{
    delete [] m_keys;
}

template <typename T, int t>
bool BBTreeNode<T, t>::thin() const
{
    return m_size == t - 1;

}

template <typename T, int t>
bool BBTreeNode<T, t>::full() const
{
    return m_size == 2 * t - 1;
}

template <typename T, int t>
bool BBTreeNode<T, t>::empty() const
{
    return m_size == 0;
}

template <typename T, int t>
void BBTreeNode<T, t>::show() const
{
    if (m_leaf)
        std::cout << "leaf node";
    else
        std::cout << "index node";
    std::cout << " keys[" << m_size << "] = [";
    for (int i = 0; i < m_size; i++)
    {
        if (i != 0)
            std::cout << ", ";
        std::cout << m_keys[i];
    }
    std::cout << "]" << std::endl;
}

template <typename T, int t>
typename BBTreeNode<T, t>::Node * BBTreeNode<T, t>::search(const T & key)
{
    Node * node = this;
    while (!node->m_leaf)
    {
        for (int i = 0; i < node->m_size; i++)
        {
            if (key < node->m_keys[i])
            {
                node = node->m_children[i];
                break;
            }
            if (i == node->m_size - 1)
            {
                node = node->m_children[i + 1];
                break;
            }
        }
    }
    for (int i = 0; i < node->m_size; i++)
    {
        if (node->m_keys[i] == key)
        {
            // found
            return node;
        }
    }
    // not found
    return nullptr;
}

template <typename T, int t>
void BBTreeNode<T, t>::traverse()
{
    int i;
    for (i = 0; i < m_size; i++)
    {
        if (!m_leaf)
            m_children[i]->traverse();
        else
            std::cout << m_keys[i] << ", ";
    }
    if (!m_leaf)
        m_children[i]->traverse();
}

template <typename T, int t>
void BBTreeNode<T, t>::split(int i)
{
    auto child = m_children[i];
    if (child->m_leaf)
    {
        split_child(i);
        m_children[i]->m_size++;
        m_keys[i] = m_children[i + 1]->m_keys[0];
    }
    else
    {
        split_child(i);
    }
}

template <typename T, int t>
void BBTreeNode<T, t>::split_child(int i)
{
    // child will be spilt into two node
    auto child = m_children[i];
    auto node = child->create(this);

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
     * 一个满的非叶子节点一共有2t-1个key，split分裂的时候，会分成左右两个节点
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
typename BBTreeNode<T, t>::Node * BBTreeNode<T, t>::leftmost()
{
    auto node = this;
    while (!node->m_leaf)
        node = node->m_children[0];
    return node;
}

template <typename T, int t>
typename BBTreeNode<T, t>::Node * BBTreeNode<T, t>::rightmost()
{
    auto node = this;
    while (!node->m_leaf)
        node = node->m_children[node->m_size];
    return node;
}

template <typename T, int t>
int BBTreeNode<T, t>::fill(int i)
{
    if (i > 0 && m_children[i - 1]->m_size >= t)
    {
        m_children[i]->take_from_left();
        return i;
    }
    else if (i < m_size && m_children[i + 1]->m_size >= t)
    {
        m_children[i]->take_from_right();
        return i;
    }
    else
    {
        if (i == m_size)
            --i;
        m_children[i]->merge();
    }
    return i;
}

template <typename T, int t>
T BBTreeNode<T, t>::predecessor(int i)
{
    auto node = m_children[i];
    while (!node->m_leaf)
        node = node->m_children[node->m_size];
    return node->m_keys[node->m_size - 1];
}

template <typename T, int t>
T BBTreeNode<T, t>::successor(int i)
{
    auto node = m_children[i + 1];
    while (!node->m_leaf)
        node = node->m_children[0];
    return node->m_keys[0];
}
