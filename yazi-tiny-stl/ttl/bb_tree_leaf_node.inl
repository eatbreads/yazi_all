template <typename T, int t>
BBTreeLeafNode<T, t>::BBTreeLeafNode(Node * parent) : BBTreeNode<T, t>(parent, true)
{
}

template <typename T, int t>
BBTreeLeafNode<T, t>::~BBTreeLeafNode()
{
}

template <typename T, int t>
typename BBTreeLeafNode<T, t>::Node * BBTreeLeafNode<T, t>::create(Node * parent)
{
    return new BBTreeLeafNode(parent);
}

template <typename T, int t>
void BBTreeLeafNode<T, t>::insert(const T & key)
{
    int i = this->m_size - 1;
    while (i >= 0 && this->m_keys[i] > key)
    {
        this->m_keys[i + 1] = this->m_keys[i];
        i--;
    }
    this->m_keys[i + 1] = key;
    this->m_size++;
}

template <typename T, int t>
void BBTreeLeafNode<T, t>::take_from_left()
{
    if (this->m_index == 0)
        throw std::logic_error("shift from left error: sibling is null");

    auto sibling = this->m_parent->m_children[this->m_index - 1];
    for (int i = this->m_size; i > 0; i--)
    {
        this->m_keys[i] = this->m_keys[i - 1];
    }
    this->m_keys[0] = sibling->m_keys[sibling->m_size - 1];
    this->m_parent->m_keys[this->m_index - 1] = this->m_keys[0];
    this->m_size++;
    sibling->m_size--;
}

template <typename T, int t>
void BBTreeLeafNode<T, t>::take_from_right()
{
    if (this->m_index == this->m_parent->m_size)
        throw std::logic_error("shift from right error: sibling is null");

    auto sibling = this->m_parent->m_children[this->m_index + 1];
    this->m_keys[this->m_size] = sibling->m_keys[0];
    this->m_parent->m_keys[this->m_index] = sibling->m_keys[1];
    for (int i = 1; i < sibling->m_size; i++)
    {
        sibling->m_keys[i - 1] = sibling->m_keys[i];
    }
    this->m_size++;
    sibling->m_size--;
}

template <typename T, int t>
void BBTreeLeafNode<T, t>::merge()
{
    auto sibling = this->m_parent->m_children[this->m_index + 1];

    // move all sibling keys into child
    for (int k = 0; k < sibling->m_size; k++)
    {
        this->m_keys[this->m_size + k] = sibling->m_keys[k];
    }

    // move all parent keys to left by one
    for (int k = this->m_index + 1; k < this->m_parent->m_size; k++)
        this->m_parent->m_keys[k - 1] = this->m_parent->m_keys[k];

    // move all parent children to left by one
    for (int k = this->m_index + 2; k <= this->m_parent->m_size; k++)
    {
        auto c = this->m_parent->m_children[k];
        this->m_parent->m_children[k - 1] = c;
        c->m_index = k - 1;
    }

    this->m_parent->m_size--;
    this->m_size += sibling->m_size;
    delete sibling;
}

template <typename T, int t>
bool BBTreeLeafNode<T, t>::remove(const T & key)
{
    int i;
    for (i = 0; i < this->m_size; i++)
    {
        if (this->m_keys[i] == key)
            break;
    }
    if (i < this->m_size)
    {
        // found the key
        for (int k = i + 1; k < this->m_size; k++)
            this->m_keys[k - 1] = this->m_keys[k];
        this->m_size--;
        return true;
    }

    // not found the key
    return false;
}