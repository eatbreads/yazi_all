template <typename T, int t>
BTree<T, t>::BTree() : m_root(nullptr), m_size(0)
{
}

template <typename T, int t>
BTree<T, t>::~BTree()
{
    clear();
}

template <typename T, int t>
void BTree<T, t>::insert(const T & key)
{
    // if tree is empty
    if (m_root == nullptr)
    {
        m_root = new Node(nullptr, true);
        m_root->insert(key);
        m_size++;
        return;
    }

    // if root is not full
    if (!m_root->full())
    {
        m_root->insert(key);
        m_size++;
        return;
    }

    // if root is full, then tree grows in height
    // create new root
    auto root = new Node(nullptr, false);

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
    root->m_children[i]->insert(key);

    // change root
    m_root = root;
    m_size++;
}

template <typename T, int t>
bool BTree<T, t>::search(const T & key)
{
    if (m_root == nullptr)
        return false;
    auto node = m_root->search(key);
    if (node == nullptr)
    {
        return false;
    }
    return true;
}

template <typename T, int t>
typename BTree<T, t>::Node * BTree<T, t>::lookup(const T & key)
{
    if (m_root == nullptr)
        return nullptr;
    return m_root->search(key);
}

template <typename T, int t>
void BTree<T, t>::remove(const T & key)
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

template <typename T, int t>
void BTree<T, t>::traverse()
{
    if (m_root != nullptr)
        m_root->traverse();
}

template <typename T, int t>
int BTree<T, t>::size() const
{
    return m_size;
}

template <typename T, int t>
bool BTree<T, t>::empty() const
{
    return m_size == 0;
}

template <typename T, int t>
bool BTree<T, t>::valid() const
{
    return valid(m_root);
}

template <typename T, int t>
bool BTree<T, t>::valid(Node * root) const
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

template <typename T, int t>
void BTree<T, t>::clear()
{
    clear(m_root);
    m_root = nullptr;
    m_size = 0;
}

template <typename T, int t>
void BTree<T, t>::swap(BTree<T, t> & other)
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

template <typename T, int t>
void BTree<T, t>::clear(Node * root)
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

template <typename T, int t>
typename BTree<T, t>::iterator BTree<T, t>::begin()
{
    if (m_root == nullptr)
        return end();
    return iterator(m_root->leftmost(), 0);
}

template <typename T, int t>
typename BTree<T, t>::iterator BTree<T, t>::end()
{
    if (m_root == nullptr)
        return iterator(m_root, -1);
    return iterator(m_root, m_root->m_size);
}

template <typename T, int t>
typename BTree<T, t>::iterator BTree<T, t>::find(const T & key)
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

template <typename T, int t>
typename BTree<T, t>::const_iterator BTree<T, t>::cbegin() const
{
    if (m_root == nullptr)
        return cend();
    return const_iterator(m_root->leftmost(), 0);
}

template <typename T, int t>
typename BTree<T, t>::const_iterator BTree<T, t>::cend() const
{
    if (m_root == nullptr)
        return const_iterator(m_root, -1);
    return const_iterator(m_root, m_root->m_size);
}

template <typename T, int t>
typename BTree<T, t>::const_iterator BTree<T, t>::find(const T & key) const
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

template <typename T, int t>
typename BTree<T, t>::reverse_iterator BTree<T, t>::rbegin()
{
    if (m_root == nullptr)
        return rend();
    auto node = m_root->rightmost();
    return reverse_iterator(node, node->m_size - 1);
}

template <typename T, int t>
typename BTree<T, t>::reverse_iterator BTree<T, t>::rend()
{
    return reverse_iterator(m_root, -1);
}

template <typename T, int t>
typename BTree<T, t>::reverse_iterator BTree<T, t>::rfind(const T & key)
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