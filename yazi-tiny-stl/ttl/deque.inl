template <typename T, int N>
Deque<T, N>::Deque() : m_size(0) {}

template <typename T, int N>
Deque<T, N>::~Deque()
{
    clear();
}

template <typename T, int N>
void Deque<T, N>::assign(int n, const T & value)
{
    clear();
    for (int i = 0; i < n; i++)
    {
        push_back(value);
    }
}

template <typename T, int N>
int Deque<T, N>::size() const  
{
    return m_size;
}

template <typename T, int N>
bool Deque<T, N>::empty() const
{
    return m_size == 0;
}

template <typename T, int N>
void Deque<T, N>::show() const
{
    std::cout << "size = " << size() << std::endl;
    for (int i = 0; i < m_nodes.size(); i++)
    {
        std::cout << "node[" << i << "] = ";
        auto node = m_nodes[i];
        for (int k = node->m_head; k < node->m_tail; k++)
        {
            std::cout << node->m_data[k] << ", ";
        }
        std::cout << std::endl;
    }
}
// size = 5  
// node[0] = 1, 2, 3,   
// node[1] = 4, 5,

template <typename T, int N>
void Deque<T, N>::push_front(const T & value)
{
    if (m_size == 0)
    {
        Node * node = new Node();
        node->m_head = node->m_tail = N;
        node->m_data[--node->m_head] = value;//这边m_head会变成7,因为一开始N默认是8,即前面还可以插8个
        m_nodes.push_back(node);
        m_size++;
        return;
    }
    Node * first = m_nodes[0];
    if (first->m_head > 0)
    {
        first->m_data[--first->m_head] = value;
        m_size++;
        return;
    }
    Node * node = new Node();
    node->m_head = node->m_tail = N;
    node->m_data[--node->m_head] = value;
    m_nodes.insert(m_nodes.begin(), node);//这边就和尾插一样,重复m_size=0的操作
    m_size++;
}

template <typename T, int N>
void Deque<T, N>::push_back(const T & value)
{
    if (m_size == 0)
    {
        Node * node = new Node();
        node->m_data[node->m_tail++] = value;
        m_nodes.push_back(node);
        m_size++;
        return;
    }
    Node * last = m_nodes[m_nodes.size() - 1];//尾插就是拿到vector的最后一个
    if (last->m_tail < N)
    {
        last->m_data[last->m_tail++] = value;
        m_size++;
        return;
    }
    Node * node = new Node();//最后一个也满了就新new出来一个
    node->m_data[node->m_tail++] = value;
    m_nodes.push_back(node);//直接push进vector,可能vector会扩容
    m_size++;
}

template <typename T, int N>
void Deque<T, N>::pop_front()
{
    if (m_size == 0)
    {
        return;
    }
    Node * first = m_nodes[0];
    if (first->m_head < first->m_tail)
    {
        first->m_head++;
        m_size--;
    }
    if (first->m_head == first->m_tail)//如果没了就把vector的第一个删了
    {
        m_nodes.erase(m_nodes.begin());//这边只是删除vector里面的指针
        delete first;                   //这边还要把实际的内存给删掉
        
    }
}

template <typename T, int N>
void Deque<T, N>::pop_back()
{
    if (m_size == 0)
    {
        return;
    }
    Node * last = m_nodes[m_nodes.size() - 1];
    if (last->m_tail > 0)
    {
        last->m_tail--;
        m_size--;
    }
    if (last->m_head == last->m_tail)
    {
        m_nodes.pop_back();
        delete last;//这边同上
    }
}

template <typename T, int N>
T & Deque<T, N>::front()
{
    if (m_size == 0)
    {
        throw std::logic_error("deque is empty");
    }
    Node * node = m_nodes[0];
    return node->m_data[node->m_head];//这边不会失败,因为如果没了他是会被整个节点一起delete的
}

template <typename T, int N>
const T & Deque<T, N>::front() const
{
    if (m_size == 0)
    {
        throw std::logic_error("deque is empty");
    }
    Node * first = m_nodes[0];
    return first->m_data[first->m_head];
}

template <typename T, int N>
T & Deque<T, N>::back()
{
    if (m_size == 0)
    {
        throw std::logic_error("deque is empty");
    }
    Node * last = m_nodes[m_nodes.size() - 1];
    return last->m_data[last->m_tail - 1];//同上
}

template <typename T, int N>
const T & Deque<T, N>::back() const
{
    if (m_size == 0)
    {
        throw std::logic_error("deque is empty");
    }
    Node * last = m_nodes[m_nodes.size() - 1];
    return last->m_data[last->m_tail - 1];
}

template <typename T, int N>
T & Deque<T, N>::at(int index)
{
    if (index < 0 || index >= m_size)
    {
        throw std::out_of_range("out of range");
    }
    return (*this)[index];//这个就是operator[]又套了一层
}

template <typename T, int N>
const T & Deque<T, N>::at(int index) const
{
    if (index < 0 || index >= m_size)
    {
        throw std::out_of_range("out of range");//这个就是operator[]又套了一层
    }
    return (*this)[index];
}

template <typename T, int N>
T & Deque<T, N>::operator [] (int index)
{
    Node * first = m_nodes[0];
    int first_size = first->m_tail - first->m_head;
    if (index < first_size)//如果第一个就找到就直接返回即可
    {
        return first->m_data[first->m_head + index];
    }
    int row = (index - first_size) / N + 1;//如果没找到就计算应该在第几行,这边要+1是因为减去了first_size
    int col = (index - first_size) % N;
    return m_nodes[row]->m_data[col];
}

template <typename T, int N>
const T & Deque<T, N>::operator [] (int index) const
{
    Node * first = m_nodes[0];
    int first_size = first->m_tail - first->m_head;
    if (index < first_size)
    {
        return first->m_data[first->m_head + index];
    }
    int row = (index - first_size) / N + 1;
    int col = (index - first_size) % N;
    return m_nodes[row]->m_data[col];
}

template <typename T, int N>
void Deque<T, N>::resize(int n)
{
    resize(n, T());
}

template <typename T, int N>
void Deque<T, N>::resize(int n, const T & value)//很一目了然
{
    if (n < m_size)
    {
        int size = m_size - n;
        for (int i = 0; i < size; i++)
        {
            pop_back();
        }
        return;
    }
    else if (n > m_size)
    {
        int size = n - m_size;
        for (int i = 0; i < size; i++)
        {
            push_back(value);
        }
    }
}

template <typename T, int N>
void Deque<T, N>::clear()
{
    if (m_size == 0)
    {
        return;
    }
    for (int i = 0; i < m_nodes.size(); i++)
    {
        delete m_nodes[i];//这边里面是Node,会递归调用内部的析构
    }
    m_nodes.clear();//然后这边调用vector的清除即可
    m_size = 0;
}

template <typename T, int N>
void Deque<T, N>::swap(Deque<T, N> & other)
{
    if (this == &other)
    {
        return;
    }
    int size = other.m_size;
    other.m_size = m_size;
    m_nodes.swap(other.m_nodes);
    m_size = size;
}

template <typename T, int N>
Deque<T, N> & Deque<T, N>::operator = (const Deque<T, N> & other)
{
    if (this == &other)
    {
        return *this;
    }
    resize(other.m_size);
    for (int i = 0; i < other.m_size; i++)
    {
        (*this)[i] = other[i];
    }
    return *this;
}

template <typename T, int N>
typename Deque<T, N>::iterator Deque<T, N>::begin()
{
    if (m_size == 0)
    {
        return end();
    }
    return iterator(m_nodes.data(), 0);
}

template <typename T, int N>
typename Deque<T, N>::iterator Deque<T, N>::end()
{
    if (m_size == 0)
    {
        return iterator();
    }
    return iterator(m_nodes.data(), m_size);//传入node*和偏移量
}

template <typename T, int N>
typename Deque<T, N>::iterator Deque<T, N>::insert(iterator pos, const T & value)
{
    resize(m_size + 1);
    int offset = pos - begin();
    for (int i = m_size; i > offset; i--)
    {
        (*this)[i] = (*this)[i - 1];//调用operator[]全体后迁
    }
    (*this)[offset] = value;
    return pos;
}

template <typename T, int N>
typename Deque<T, N>::iterator Deque<T, N>::erase(iterator pos)
{
    int offset = pos - begin();
    for (int i = offset + 1; i < m_size; i++)
    {
        (*this)[i - 1] = (*this)[i];//全体前迁
    }
    resize(m_size - 1);
    if (m_size == 0)
        return end();
    else
        return pos;
}

template <typename T, int N>
typename Deque<T, N>::const_iterator Deque<T, N>::cbegin() const
{
    if (m_size == 0)
    {
        return cend();
    }
    return const_iterator((Node **)m_nodes.data(), 0);
}

template <typename T, int N>
typename Deque<T, N>::const_iterator Deque<T, N>::cend() const
{
    if (m_size == 0)
    {
        return const_iterator();
    }
    return const_iterator((Node **)m_nodes.data(), m_size);
}

template <typename T, int N>
typename Deque<T, N>::reverse_iterator Deque<T, N>::rbegin()
{
    if (m_size == 0)
    {
        return rend();
    }
    return reverse_iterator(m_nodes.data(), m_size - 1);
}

template <typename T, int N>
typename Deque<T, N>::reverse_iterator Deque<T, N>::rend()
{
    if (m_size == 0)
    {
        return reverse_iterator();
    }
    return reverse_iterator(m_nodes.data(), -1);
}