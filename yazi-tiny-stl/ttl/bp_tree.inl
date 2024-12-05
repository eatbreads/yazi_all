template <typename T, typename D, int t>
BPTree<T, D, t>::BPTree() : m_root(nullptr), m_size(0)
{
}

template <typename T, typename D, int t>
BPTree<T, D, t>::~BPTree()
{
    clear();
}

template <typename T, typename D, int t>
void BPTree<T, D, t>::insert(const T & key, const D & data)
{
    // if tree is empty
    if (m_root == nullptr)
    {
        m_root = create_node(nullptr, true);
        m_root->insert(key, data);
        m_size++;
        return;
    }

    // if root is not full
    if (!m_root->full())
    {
        m_root->insert(key, data);
        m_size++;
        return;
    }

    // if root is full, then tree grows in height
    // create new root
    auto root = create_node(nullptr, false);

    // make old root as child of new root
    root->m_children[0] = m_root;
    m_root->m_parent = root;

    // split the old root and move 1 key to the new root
    root->split(0);

    // new root has two children now. Decide which of the
    // two children is going to have new key
    int i = 0;
    if (root->m_keys[i] < key)
        i++;
    root->m_children[i]->insert(key, data);

    // change root
    m_root = root;
    m_size++;
}

template <typename T, typename D, int t>
bool BPTree<T, D, t>::search(const T & key)
{
    if (m_root == nullptr)
        return false;
    auto node = m_root->search(key);
    if (node == nullptr)
        return false;
    else
        return true;
}

template <typename T, typename D, int t>
typename BPTree<T, D, t>::Node * BPTree<T, D, t>::lookup(const T & key, bool leaf)
{
    if (m_root == nullptr)
        return nullptr;
    if (leaf)
        return m_root->search(key);

    Node * node = m_root;
    while (!node->m_leaf)
    {
        for (int i = 0; i < node->m_size; i++)
        {
            if (key == node->m_keys[i])
            {
                // found
                return node;
            }
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
    // not found
    return nullptr;
}

template <typename T, typename D, int t>
void BPTree<T, D, t>::remove(const T & key)
{
    // tree is empty
    if (m_root == nullptr)
        return;

    if (m_root->remove(key))
        m_size--;

    if (m_root->m_size == 0)
    {
        auto temp = m_root;
        if (m_root->m_leaf)
        {
            m_root = nullptr;
        }
        else
        {
            m_root = m_root->m_children[0];
            m_root->m_parent = nullptr;
        }
        delete temp;
    }
}

template <typename T, typename D, int t>
void BPTree<T, D, t>::traverse()
{
    if (m_root != nullptr)
        m_root->traverse();
}

template <typename T, typename D, int t>
int BPTree<T, D, t>::size() const
{
    return m_size;
}

template <typename T, typename D,  int t>
bool BPTree<T, D, t>::empty() const
{
    return m_size == 0;
}

template <typename T, typename D,  int t>
bool BPTree<T, D, t>::valid() const
{
    return valid(m_root);
}

template <typename T, typename D,  int t>
bool BPTree<T, D, t>::valid(Node * root) const
{
    if (root == nullptr)
        return true;
    if (root != m_root)
    {
        if (root->m_size < t - 1)
            return false;
    }
    if (root->m_size > 2 * t - 1)
        return false;
    for (int i = 1; i < root->m_size; i++)
    {
        if (root->m_keys[i - 1] >= root->m_keys[i])
            return false;
    }
    if (root->m_leaf)
        return true;

    for (int i = 0; i <= root->m_size; i++)
    {
        if (root->m_children[i]->m_parent != root)
            return false;
        if (root->m_children[i]->m_index != i)
            return false;
        if (!valid(root->m_children[i]))
            return false;
    }
    return true;
}

template <typename T, typename D, int t>
void BPTree<T, D, t>::clear()
{
    clear(m_root);
    m_root = nullptr;
    m_size = 0;
}

template <typename T, typename D, int t>
void BPTree<T, D, t>::swap(BPTree<T, D, t> & other)
{
    if (this == &other)
    {
        return;
    }
    auto root = other.m_root;
    int size = other.m_size;
    other.m_root = m_root;
    other.m_size = m_size;
    m_root = root;
    m_size = size;
}

template <typename T, typename D, int t>
void BPTree<T, D, t>::clear(Node * root)
{
    if (root == nullptr)
        return;
    if (!root->m_leaf)
    {
        for (int i = 0; i <= root->m_size; i++)
        {
            clear(root->m_children[i]);
        }
    }
    delete root;
}

template <typename T, typename D, int t>
typename BPTree<T, D, t>::Node * BPTree<T, D, t>::create_node(Node * parent, bool leaf)
{
    if (leaf)
        return new BPTreeLeafNode<T, D, t>(parent);
    else
        return new BPTreeIndexNode<T, D, t>(parent);
}

template <typename T, typename D, int t>
typename BPTree<T, D, t>::iterator BPTree<T, D, t>::begin()
{
    if (m_root == nullptr)
        return end();
    auto node = m_root->leftmost();
    return iterator(node, 0);
}

template <typename T, typename D, int t>
typename BPTree<T, D, t>::iterator BPTree<T, D, t>::end()
{
    if (m_root == nullptr)
        return iterator();
    auto node = m_root->rightmost();
    return iterator(node, node->m_size);
}

template <typename T, typename D, int t>
typename BPTree<T, D, t>::iterator BPTree<T, D, t>::find(const T & key)
{
    if (m_root == nullptr)
        return end();
    auto node = m_root->search(key);
    if (node == nullptr)
        return end();
    int i;
    for (i = 0; i < node->m_size; i++)
        if (node->m_keys[i] == key)
            break;
    return iterator(node, i);
}

template <typename T, typename D, int t>
typename BPTree<T, D, t>::const_iterator BPTree<T, D, t>::cbegin() const
{
    if (m_root == nullptr)
        return cend();
    auto node = m_root->leftmost();
    return const_iterator(node, 0);
}

template <typename T, typename D, int t>
typename BPTree<T, D, t>::const_iterator BPTree<T, D, t>::cend() const
{
    if (m_root == nullptr)
        return const_iterator();
    auto node = m_root->rightmost();
    return const_iterator(node, node->m_size);
}

template <typename T, typename D, int t>
typename BPTree<T, D, t>::const_iterator BPTree<T, D, t>::find(const T & key) const
{
    if (m_root == nullptr)
        return cend();
    auto node = m_root->search(key);
    if (node == nullptr)
        return cend();
    int i;
    for (i = 0; i < node->m_size; i++)
        if (node->m_keys[i] == key)
            break;
    return const_iterator(node, i);
}

template <typename T, typename D, int t>
typename BPTree<T, D, t>::reverse_iterator BPTree<T, D, t>::rbegin()
{
    if (m_root == nullptr)
        return rend();
    auto node = m_root->rightmost();
    return reverse_iterator(node, node->m_size - 1);
}

template <typename T, typename D, int t>
typename BPTree<T, D, t>::reverse_iterator BPTree<T, D, t>::rend()
{
    if (m_root == nullptr)
        return reverse_iterator();
    auto node = m_root->leftmost();
    return reverse_iterator(node, -1);
}

template <typename T, typename D, int t>
typename BPTree<T, D, t>::reverse_iterator BPTree<T, D, t>::rfind(const T & key)
{
    if (m_root == nullptr)
        return rend();
    auto node = m_root->search(key);
    if (node == nullptr)
        return rend();
    int i;
    for (i = 0; i < node->m_size; i++)
        if (node->m_keys[i] == key)
            break;
    return reverse_iterator(node, i);
}