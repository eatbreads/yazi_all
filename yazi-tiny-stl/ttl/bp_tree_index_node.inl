template <typename T, typename D, int t>
BPTreeIndexNode<T, D, t>::BPTreeIndexNode(Node * parent) : BPTreeNode<T, D, t>(parent, false)
{
    this->m_children = new Node *[2 * t];
    std::memset(this->m_children, 0, sizeof(Node *) * 2 * t);
}

template <typename T, typename D, int t>
BPTreeIndexNode<T, D, t>::~BPTreeIndexNode()
{
    delete [] this->m_children;
}

template <typename T, typename D, int t>
typename BPTreeIndexNode<T, D, t>::Node * BPTreeIndexNode<T, D, t>::create(Node * parent)
{
    return new BPTreeIndexNode<T, D, t>(parent);
}

template <typename T, typename D, int t>
void BPTreeIndexNode<T, D, t>::insert(const T & key, const D & data)
{
    int i = 0;
    while (i < this->m_size && key >= this->m_keys[i])
        i++;
    if (this->m_children[i]->full())
    {
        this->split(i);
        if (this->m_keys[i] < key)
            i++;
    }
    this->m_children[i]->insert(key, data);
}

template <typename T, typename D, int t>
void BPTreeIndexNode<T, D, t>::take_from_left()
{
    if (this->m_index == 0)
        throw std::logic_error("shift from left error: sibling is null");

    auto sibling = this->m_parent->m_children[this->m_index - 1];
    for (int i = this->m_size; i > 0; i--)
    {
        this->m_keys[i] = this->m_keys[i - 1];
    }
    this->m_keys[0] = this->m_parent->m_keys[this->m_index - 1];
    this->m_parent->m_keys[this->m_index - 1] = sibling->m_keys[sibling->m_size - 1];
    for (int i = this->m_size; i >= 0; i--)
    {
        this->m_children[i + 1] = this->m_children[i];
        this->m_children[i + 1]->m_index = i + 1;
    }
    auto child = sibling->m_children[sibling->m_size];
    child->m_parent = this;
    child->m_index = 0;
    this->m_children[0] = child;
    this->m_size++;
    sibling->m_size--;
}

template <typename T, typename D, int t>
void BPTreeIndexNode<T, D, t>::take_from_right()
{
    if (this->m_index == this->m_parent->m_size - 1)
        throw std::logic_error("shift from right error: sibling is null");

    auto sibling = this->m_parent->m_children[this->m_index + 1];
    this->m_keys[this->m_size] = this->m_parent->m_keys[this->m_index];
    this->m_parent->m_keys[this->m_index] = sibling->m_keys[0];
    for (int i = 0; i < sibling->m_size - 1; i++)
    {
        sibling->m_keys[i] = sibling->m_keys[i + 1];
    }
    auto child = sibling->m_children[0];
    child->m_parent = this;
    child->m_index = this->m_size + 1;
    this->m_children[this->m_size + 1] = child;
    for (int i = 0; i < sibling->m_size; i++)
    {
        sibling->m_children[i] = sibling->m_children[i + 1];
        sibling->m_children[i]->m_index = i;
    }
    this->m_size++;
    sibling->m_size--;
}

template <typename T, typename D, int t>
void BPTreeIndexNode<T, D, t>::merge()
{
    auto sibling = this->m_parent->m_children[this->m_index + 1];

    // move one parent key into child
    this->m_keys[this->m_size] = this->m_parent->m_keys[this->m_index];

    // move all sibling keys into child
    for (int k = 0; k < sibling->m_size; k++)
    {
        this->m_keys[this->m_size + 1 + k] = sibling->m_keys[k];
    }

    // move all sibling children into child
    for (int k = 0; k <= sibling->m_size; k++)
    {
        auto c = sibling->m_children[k];
        this->m_children[this->m_size + 1 + k] = c;
        c->m_parent = this;
        c->m_index = this->m_size + 1 + k;
    }

    // move parent all parent keys to left by one
    for (int k = this->m_index + 1; k < this->m_parent->m_size; k++)
        this->m_parent->m_keys[k - 1] = this->m_parent->m_keys[k];

    // move move all parent children to left by one
    for (int k = this->m_index + 2; k <= this->m_parent->m_size; k++)
    {
        auto c = this->m_parent->m_children[k];
        this->m_parent->m_children[k - 1] = c;
        c->m_index = k - 1;
    }

    this->m_parent->m_size--;
    this->m_size += sibling->m_size + 1;
    delete sibling;
}

template <typename T, typename D, int t>
bool BPTreeIndexNode<T, D, t>::remove(const T & key)
{
    int i = 0;
    while (i < this->m_size && this->m_keys[i] <= key)
        i++;
    if (this->m_children[i]->m_size < t)
    {
        i = this->fill(i);
    }
    bool ret = this->m_children[i]->remove(key);
    for (int k = 0; k < this->m_size; k++)
    {
        if (this->m_keys[k] == key)
        {
            T repl = this->successor(k);
            this->m_keys[k] = repl;
            break;
        }
    }
    return ret;
}