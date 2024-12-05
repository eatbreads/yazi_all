template <typename T, int max_level>
SkipList<T, max_level>::SkipList() : m_p(0.5)//默认构造的mp为0.5
{
    m_head = new Node(T(), max_level);
    m_size = 0;
    m_level = 0;

    // seed random number generator
    //这边应该是设置种子
    srand(time(0));
}

template <typename T, int max_level>
SkipList<T, max_level>::SkipList(float p) : m_p(p)
{
    m_head = new Node(T(), max_level);
    m_size = 0;
    m_level = 0;

    // seed random number generator
    srand(time(0));
}

template <typename T, int max_level>
SkipList<T, max_level>::~SkipList()
{
    clear();
    if (m_head != nullptr)
    {
        delete m_head;
        m_head = nullptr;
    }
}

template <typename T, int max_level>
int SkipList<T, max_level>::random_level()
{
    int level = 1;
    //RAND_MAX是rand()函数能返回的最大值,所以p其实是几乎为0-1均匀分布的随机数
    float p = (float)rand() / RAND_MAX;
    while (p < m_p && level < max_level)//m_p为概率,即小于0.5才算成功
    {
        level++;//抛硬币,成功一次就进这个循环一次使得level++
        p = (float)rand() / RAND_MAX;
    }
    return level;
}

template <typename T, int max_level>
typename SkipList<T, max_level>::Node * SkipList<T, max_level>::search(const T & value)
{
    Node * node = m_head;
    for (int i = m_level - 1; i >= 0; i--)//表示最多只要下楼level-1次,且每个节点不需要遍历每一层楼
    {//如果当前顶楼的所指节点小于目标值就到所指节点
        while (node->m_forward[i] != nullptr && node->m_forward[i]->m_value < value)
        {
            node = node->m_forward[i];
        }
        //如果等于就返回节点,不等于就会到for循环下楼(表示所指节点比目标值大)
        if (node->m_forward[i] != nullptr && node->m_forward[i]->m_value == value)
        {
            return node->m_forward[i];
        }
    }
    return nullptr;
}

template <typename T, int max_level>
bool SkipList<T, max_level>::empty() const
{
    return m_size == 0;
}

template <typename T, int max_level>
int SkipList<T, max_level>::size() const
{
    return m_size;
}

template <typename T, int max_level>
bool SkipList<T, max_level>::insert(const T & value)
{
    Node * update[max_level] = {nullptr};//在栈区开一个数组
    Node * node = m_head;
    for (int i = m_level - 1; i >= 0; i--)
    {
        while (node->m_forward[i] != nullptr && node->m_forward[i]->m_value < value)
        {
            node = node->m_forward[i];
        }
        if (node->m_forward[i] != nullptr && node->m_forward[i]->m_value == value)
        {
            return false;//这边表示已经存在节点了就返回错误
        }
        update[i] = node;//下楼一次就把节点放入update数组
    }

    int level = random_level();//为新节点设置层级
    if (level > m_level)//这边表示如果新的层级数大于当前最大层级
    {
        for (int i = m_level; i < level; i++)
        {
            update[i] = m_head;//只有头节点是最大层级的前继节点,在这边设置后给下面更新
        }
        m_level = level;///更新最大层级
    }

    node = new Node(value, level);
    for (int i = 0; i < level; i++)//更新此层级数的前继节点(存在update中)
    {
        node->m_forward[i] = update[i]->m_forward[i];//更新自身的后继节点,指向前继节点的后继
        update[i]->m_forward[i] = node;//把需要更新的前继节点指向当前节点
    }
    m_size++;
    return true;
}

template <typename T, int max_level>
void SkipList<T, max_level>::remove(const T &value)
{
    Node * update[max_level] = {nullptr};
    Node * node = m_head;
    for (int i = m_level - 1; i >= 0; i--)//这个是往下的循环
    {//这个函数不找节点,只是统计update
        while (node->m_forward[i] != nullptr && node->m_forward[i]->m_value < value)
        {
            node = node->m_forward[i];//这边是往右的循环
        }
        update[i] = node;//往下一次就加入一次update
    }

    Node * temp = nullptr; 
    for (int i = m_level - 1; i >= 0; i--)
    {
        node = update[i];//遍历可能需要update的节点,如果下一节点是要删除节点就指向被删除节点的后继节点
        if (node->m_forward[i] != nullptr && node->m_forward[i]->m_value == value)
        {
            temp = node->m_forward[i];//找到待删除节点
            node->m_forward[i] = temp->m_forward[i];
        }
    }
    if (temp != nullptr)//如果找到了待删除节点
    {
        m_size--;
        delete temp;
    }

    // remove levels having no elements
    for (int i = m_level - 1; i >= 0; i--)
    {
        if (m_head->m_forward[i] != nullptr)//如果一整层节点都没有元素了就level--
            break;
        m_level--;
    }
}

template <typename T, int max_level>
T & SkipList<T, max_level>::front()
{
    if (m_size == 0)
    {
        throw std::logic_error("skip list is empty");
    }
    return m_head->m_forward[0]->m_value;
}

template <typename T, int max_level>
const T & SkipList<T, max_level>::front() const
{
    if (m_size == 0)
    {
        throw std::logic_error("skip list is empty");
    }
    return m_head->m_forward[0]->m_value;
}

template <typename T, int max_level>
T & SkipList<T, max_level>::back()
{
    Node * node = m_head;
    for (int i = m_level - 1; i >= 0; i--)
    {
        while (node->m_forward[i] != nullptr)
        {
            node = node->m_forward[i];
        }
    }
    return node->m_value;
}

template <typename T, int max_level>
const T & SkipList<T, max_level>::back() const
{
    Node * node = m_head;
    for (int i = m_level - 1; i >= 0; i--)
    {
        while (node->m_forward[i] != nullptr)
        {
            node = node->m_forward[i];
        }
    }
    return node->m_value;
}

template <typename T, int max_level>
void SkipList<T, max_level>::clear()
{
    if (m_size == 0)
    {
        return;
    }
    Node * node = m_head->m_forward[0];
    while (node != nullptr)//从头删到尾
    {
        Node * temp = node;
        node = node->m_forward[0];
        delete temp;
    }
    m_size = 0;
    m_level = 0;
    for (int i = 0; i < max_level; i++)
    {
        m_head->m_forward[i] = nullptr;//把头节点的后节点置空(头节点不删)
    }
}

template <typename T, int max_level>
typename SkipList<T, max_level>::iterator SkipList<T, max_level>::begin()
{
    if (m_size == 0)
    {
        return end();
    }
    return iterator(m_head->m_forward[0]);
}

template <typename T, int max_level>
typename SkipList<T, max_level>::iterator SkipList<T, max_level>::end()
{
    return iterator();
}

template <typename T, int max_level>
typename SkipList<T, max_level>::iterator SkipList<T, max_level>::find(const T & value)
{
    auto node = search(value);
    return iterator(node);
}

template <typename T, int max_level>
typename SkipList<T, max_level>::const_iterator SkipList<T, max_level>::cbegin() const
{
    if (m_size == 0)
    {
        return cend();
    }
    return const_iterator(m_head->m_forward[0]);
}

template <typename T, int max_level>
typename SkipList<T, max_level>::const_iterator SkipList<T, max_level>::cend() const
{ 
    return const_iterator();
}

template <typename T, int max_level>
typename SkipList<T, max_level>::const_iterator SkipList<T, max_level>::find(const T & value) const
{
    auto node = search(value);//就是封装了search
    return const_iterator(node);
}

template <typename T, int max_level>
void SkipList<T, max_level>::show() const
{
    std::cout << "skip list size=" << m_size << ", level=" << m_level << ", max_level=" << max_level << ", p=" << m_p << std::endl;
    for (int i = 0; i < m_level; i++)
    {
        Node * node = m_head->m_forward[i];
        std::cout << "level[" << i << "] : ";
        while (node != nullptr)
        {
            std::cout << node->m_value << " -> ";
            node = node->m_forward[i];
        }
        std::cout << "\n";
    }
}
//输出结果应该如下所示
// skip list size=N, level=L, max_level=M, p=P  
// level[0] : value1 -> value2 -> ... -> valueN ->   
// level[1] : value1' -> value3' -> ... ->  ->   
// level[2] : value1'' -> value5'' ->  ->   
// ...  
// level[L-1] : valueX ->  ->