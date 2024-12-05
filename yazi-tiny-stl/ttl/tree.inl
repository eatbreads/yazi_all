template <typename T>
Tree<T>::Tree() : m_root(nullptr), m_size(0) {}

template <typename T>
Tree<T>::~Tree()
{
    clear();
}

template <typename T>
bool Tree<T>::search(const T & key)
{
    return search(m_root, key);//把根节点传进去
}

template <typename T>
bool Tree<T>::valid(Node * root) const
{
    if (root == nullptr)//空节点即为合法
        return true;
    if (root->m_left == nullptr && root->m_right == nullptr)
        return true;
    if (root->m_left != nullptr && root->m_right == nullptr)//如果有左孩子
    {
        if (root->m_key < root->m_left->m_key)//检查当前节点是否有效
            return false;
        if (root->m_left->m_parent != root)
            return false;
        return valid(root->m_left);//就递归进去左孩子查看是否有效
    }
    else if (root->m_left == nullptr && root->m_right != nullptr)
    {
        if (root->m_key > root->m_right->m_key)//右孩子同理
            return false;
        if (root->m_right->m_parent != root)
            return false;
        return valid(root->m_right);
    }
    else
    {
        if (root->m_key < root->m_left->m_key)//如果两个孩子都有
            return false;
        if (root->m_left->m_parent != root)
            return false;
        if (root->m_key > root->m_right->m_key)//也是检查当前节点是否有效
            return false;
        if (root->m_right->m_parent != root)
            return false;
        return valid(root->m_left) && valid(root->m_right);//然后与一下左右孩子的valid
    }
}

template <typename T>
bool Tree<T>::search(Node * root, const T & key)
{
    if (root == nullptr)//这个根节点是广义的根节点,每个节点都可以是根节点
        return false;
    if (root->m_key > key)
        return search(root->m_left, key);
    else if (root->m_key < key)
        return search(root->m_right, key);
    else
    return true;//只有都不进去(即root->key既不小于也不大于,即等于)才会执行到这里
}

template <typename T>
int Tree<T>::size() const
{
    return m_size;
}

template <typename T>
bool Tree<T>::empty() const
{
    return m_size == 0;
}

template <typename T>
bool Tree<T>::valid() const
{
    return valid(m_root);
}

template <typename T>
void Tree<T>::clear()
{
    clear(m_root);
    m_root = nullptr;
    m_size = 0;
}

template <typename T>
void Tree<T>::swap(Tree<T> & other)
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

template <typename T>
void Tree<T>::clear(Node * root)
{
    if (root == nullptr)
        return;
    clear(root->m_left);
    clear(root->m_right);
    delete root;
}

template <typename T>
typename Tree<T>::iterator Tree<T>::begin()
{
    if (m_root == nullptr)
        return end();
    return iterator(m_root, m_root->leftmost());
}

template <typename T>
typename Tree<T>::iterator Tree<T>::end()
{
    return iterator(m_root, nullptr);
}

template <typename T>
typename Tree<T>::iterator Tree<T>::find(const T & key)
{
    if (m_root == nullptr)
        return end();
    auto node = m_root->search(key);
    return iterator(m_root, node);
}

template <typename T>
typename Tree<T>::const_iterator Tree<T>::cbegin() const
{
    if (m_root == nullptr)
        return cend();
    return const_iterator(m_root, m_root->leftmost());
}

template <typename T>
typename Tree<T>::const_iterator Tree<T>::cend() const
{
    return const_iterator(m_root, nullptr);
}

template <typename T>
typename Tree<T>::const_iterator Tree<T>::find(const T & key) const
{
    if (m_root == nullptr)
        return cend();
    auto node = m_root->search(key);
    return const_iterator(m_root, node);
}

template <typename T>
typename Tree<T>::reverse_iterator Tree<T>::rbegin()
{
    if (m_root == nullptr)
        return rend();
    return reverse_iterator(m_root, m_root->rightmost());
}

template <typename T>
typename Tree<T>::reverse_iterator Tree<T>::rend()
{
    return reverse_iterator(m_root, nullptr);
}

template <typename T>
typename Tree<T>::reverse_iterator Tree<T>::rfind(const T & key)
{
    if (m_root == nullptr)
        return rend();
    auto node = m_root->search(key);
    return reverse_iterator(m_root, node);
}

template <typename T>
void Tree<T>::show() const
{
    std::cout << "size=" << m_size << std::endl;
    inorder(m_root);
    std::cout << std::endl;
}

template <typename T>
void Tree<T>::preorder(Node * root) const
{
    if (root == nullptr)
        return;
    std::cout << root->m_key << ", ";
    preorder(root->m_left);
    preorder(root->m_right);
}

template <typename T>
void Tree<T>::inorder(Node * root) const
{
    if (root == nullptr)
        return;
    inorder(root->m_left);
    std::cout << root->m_key << ", ";
    inorder(root->m_right);
}

template <typename T>
void Tree<T>::postorder(Node * root) const
{
    if (root == nullptr)
        return;
    inorder(root->m_left);
    inorder(root->m_right);
    std::cout << root->m_key << ", ";
}