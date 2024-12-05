template <typename T, typename D, int t>
BPTreeLeafNode<T, D, t>::BPTreeLeafNode(Node * parent) : BPTreeNode<T, D, t>(parent, true)
{
    m_data = new D[2 * t - 1];
    std::memset(m_data, 0, sizeof(D) * (2 * t - 1));
    m_prev = m_next = nullptr;
}

template <typename T, typename D, int t>
BPTreeLeafNode<T, D, t>::~BPTreeLeafNode()
{
    delete [] m_data;
}

template <typename T, typename D, int t>
typename BPTreeLeafNode<T, D, t>::Node * BPTreeLeafNode<T, D, t>::create(Node * parent)
{
    return new BPTreeLeafNode<T, D, t>(parent);
}

template <typename T, typename D, int t>
void BPTreeLeafNode<T, D, t>::insert(const T & key, const D & data)
{
    int i = this->m_size - 1;
    while (i >= 0 && this->m_keys[i] > key)
    {
        this->m_keys[i + 1] = this->m_keys[i];
        this->m_data[i + 1] = this->m_data[i];
        i--;
    }
    this->m_keys[i + 1] = key;
    this->m_data[i + 1] = data;
    this->m_size++;
}

template <typename T, typename D, int t>
void BPTreeLeafNode<T, D, t>::take_from_left()
{
    if (this->m_index == 0)
        throw std::logic_error("shift from left error: sibling is null");

    auto sibling = (BPTreeLeafNode<T, D, t> *)this->m_parent->m_children[this->m_index - 1];
    for (int i = this->m_size; i > 0; i--)
    {
        this->m_keys[i] = this->m_keys[i - 1];
        this->m_data[i] = this->m_data[i - 1];
    }
    this->m_keys[0] = sibling->m_keys[sibling->m_size - 1];
    this->m_data[0] = sibling->m_data[sibling->m_size - 1];
    this->m_parent->m_keys[this->m_index - 1] = this->m_keys[0];
    this->m_size++;
    sibling->m_size--;
}

template <typename T, typename D, int t>
void BPTreeLeafNode<T, D, t>::take_from_right()
{
    if (this->m_index == this->m_parent->m_size - 1)
        throw std::logic_error("shift from right error: sibling is null");

    auto sibling = (BPTreeLeafNode<T, D, t> *)this->m_parent->m_children[this->m_index + 1];
    this->m_keys[this->m_size] = sibling->m_keys[0];
    this->m_data[this->m_size] = sibling->m_data[0];
    this->m_parent->m_keys[this->m_index] = sibling->m_keys[1];
    for (int i = 1; i < sibling->m_size; i++)
    {
        sibling->m_keys[i - 1] = sibling->m_keys[i];
        sibling->m_data[i - 1] = sibling->m_data[i];
    }
    this->m_size++;
    sibling->m_size--;
}

template <typename T, typename D, int t>
void BPTreeLeafNode<T, D, t>::merge()
{
    auto sibling = (BPTreeLeafNode<T, D, t> *)this->m_parent->m_children[this->m_index + 1];

    // move all sibling keys into child
    for (int k = 0; k < sibling->m_size; k++)
    {
        this->m_keys[this->m_size + k] = sibling->m_keys[k];
        this->m_data[this->m_size + k] = sibling->m_data[k];
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

    m_next = sibling->m_next;
    if (sibling->m_next != nullptr)
        ((BPTreeLeafNode<T, D, t> *)sibling->m_next)->m_prev = this;
    delete sibling;
}

template <typename T, typename D, int t>
bool BPTreeLeafNode<T, D, t>::remove(const T & key)
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
        {
            this->m_keys[k - 1] = this->m_keys[k];
            this->m_data[k - 1] = this->m_data[k];
        }
        this->m_size--;
        return true;
    }

    // not found the key
    return false;
}