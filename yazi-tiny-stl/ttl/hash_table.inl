template <typename T, typename Hash>
HashTable<T, Hash>::HashTable()
{
    m_bucket_count = get_prime(8);
    m_buckets = buckets_create(m_bucket_count);
    m_size = 0;
    m_max_load_factor = 1.0;//负载因子和unorder_map一样
}

template <typename T, typename Hash> 
HashTable<T, Hash>::~HashTable()
{
    clear();
    if (m_buckets != nullptr)
    {
        delete m_buckets;
        m_buckets = nullptr;
    }
}

template <typename T, typename Hash>
bool HashTable<T, Hash>::insert(const T & key)
{
    if (load_factor() > max_load_factor())//查看负载因子
        rehash(m_bucket_count * 2);//扩容桶数量
    auto result = buckets_insert(m_buckets, m_bucket_count, key);
    if (result)
        m_size++;
    return result;
}

template <typename T, typename Hash>
bool HashTable<T, Hash>::remove(const T & key)
{
    auto result = buckets_remove(m_buckets, m_bucket_count, key);
    if (result)
        m_size--;
    return result;
}

template <typename T, typename Hash>
bool HashTable<T, Hash>::search(const T & key)
{
    auto node = buckets_search(m_buckets, m_bucket_count, key);
    return node != nullptr;
}

template <typename T, typename Hash>
bool HashTable<T, Hash>::empty() const
{
    return m_size == 0;
}

template <typename T, typename Hash>
int HashTable<T, Hash>::size() const
{
    return m_size;
}

template <typename T, typename Hash>
int HashTable<T, Hash>::bucket(const T & key) const
{
    size_t hashcode = m_hash(key);
    return hashcode % m_bucket_count;
}

template <typename T, typename Hash>
int HashTable<T, Hash>::bucket_count() const
{
    return m_bucket_count;
}

template <typename T, typename Hash>
int HashTable<T, Hash>::bucket_size(int slot) const
{
    int count = 0;
    auto node = m_buckets[slot];
    while (node != nullptr)
    {
        count++;
        node = node->m_next;
    }
    return count;
}

template <typename T, typename Hash>
int HashTable<T, Hash>::count(const T & key) const
{
    if (search(key))
        return 1;
    else
        return 0;
}

template <typename T, typename Hash>
float HashTable<T, Hash>::load_factor() const
{
    return m_size * 1.0 / m_bucket_count;
}

template <typename T, typename Hash>
float HashTable<T, Hash>::max_load_factor() const
{
    return m_max_load_factor;
}

template <typename T, typename Hash>
void HashTable<T, Hash>::max_load_factor(float f)
{
    m_max_load_factor = f;
}

template <typename T, typename Hash>
Hash HashTable<T, Hash>::hash_function() const
{
    return m_hash;
}

template <typename T, typename Hash>
void HashTable<T, Hash>::rehash(int n)
{
    if (n <= m_bucket_count)
        return;
    int bucket_count = get_prime(n);
    Node ** buckets = buckets_create(bucket_count);
    for (int i = 0; i < m_bucket_count; i++)
    {
        auto node = m_buckets[i];
        while (node != nullptr)
        {
            auto next = node->m_next;
            buckets_migrate(buckets, bucket_count, node);
            node = next;
        }
    }
    delete [] m_buckets;
    m_buckets = buckets;
    m_bucket_count = bucket_count;
}

template <typename T, typename Hash>
void HashTable<T, Hash>::clear()
{
    buckets_destroy(m_buckets, m_bucket_count);
    m_size = 0;
}

template <typename T, typename Hash>
void HashTable<T, Hash>::swap(HashTable<T> & other)
{
    Node ** buckets = other.m_buckets;
    int bucket_count = other.m_bucket_count;
    int size = other.m_size;
    Hash hash = other.m_hash;
    float max_load_factor = other.m_max_load_factor;

    other.m_buckets = m_buckets;
    other.m_bucket_count = m_bucket_count;
    other.m_size = m_size;
    other.m_hash = m_hash;
    other.m_max_load_factor = m_max_load_factor;

    m_buckets = buckets;
    m_bucket_count = bucket_count;
    m_size = size;
    m_hash = hash;
    m_max_load_factor = max_load_factor;
}

template <typename T, typename Hash>
void HashTable<T, Hash>::show() const
{
    std::cout << "size = " << m_size << std::endl;
    std::cout << "bucket_count = " << m_bucket_count << std::endl;
    std::cout << "load_factory = " << load_factor() << std::endl;
    std::cout << "max_load_factory = " << max_load_factor() << std::endl;
    for (int i = 0; i < m_bucket_count; i++)
    {
        auto node = m_buckets[i];
        while (node != nullptr)
        {
            std::cout << node->m_key << ", ";
            node = node->m_next;
        }
    }
    std::cout << std::endl;
}

template <typename T, typename Hash>
typename HashTable<T, Hash>::iterator HashTable<T, Hash>::begin()
{
    if (m_buckets == nullptr)
        return end();
    int slot = 0;
    while (slot < m_bucket_count && m_buckets[slot] == nullptr)
        slot++;
    if (slot == m_bucket_count)
        return end();
    return iterator(m_buckets, m_buckets[slot], m_bucket_count, slot);
}

template <typename T, typename Hash>
typename HashTable<T, Hash>::iterator HashTable<T, Hash>::end()
{
    return iterator(m_buckets, nullptr, m_bucket_count, m_bucket_count);
}

template <typename T, typename Hash>
typename HashTable<T, Hash>::iterator HashTable<T, Hash>::find(const T & key)
{
    size_t hashcode = m_hash(key);
    int slot = hashcode % m_bucket_count;
    if (m_buckets[slot] != nullptr)
    {
        auto node = m_buckets[slot];
        while (node != nullptr)
        {
            if (node->m_key == key)
                return iterator(m_buckets, node, m_bucket_count, slot);
            node = node->m_next;
        }
    }
    return end();
}

template <typename T, typename Hash>
typename HashTable<T, Hash>::const_iterator HashTable<T, Hash>::cbegin() const
{
    if (m_buckets == nullptr)
        return cend();
    int slot = 0;
    while (slot < m_bucket_count && m_buckets[slot] == nullptr)
        slot++;
    if (slot == m_bucket_count)
        return cend();
    return const_iterator(m_buckets, m_buckets[slot], m_bucket_count, slot);
}

template <typename T, typename Hash>
typename HashTable<T, Hash>::const_iterator HashTable<T, Hash>::cend() const
{
    return const_iterator(m_buckets, nullptr, m_bucket_count, m_bucket_count);
}

template <typename T, typename Hash>
typename HashTable<T, Hash>::const_iterator HashTable<T, Hash>::find(const T & key) const
{
    size_t hashcode = m_hash(key);
    int slot = hashcode % m_bucket_count;
    if (m_buckets[slot] != nullptr)
    {
        auto node = m_buckets[slot];
        while (node != nullptr)
        {
            if (node->m_key == key)
                return const_iterator(m_buckets, node, m_bucket_count, slot);
            node = node->m_next;
        }
    }
    return cend();
}

template <typename T, typename Hash>
bool HashTable<T, Hash>::check_prime(int n)
{
    if (n == 0 || n == 1)//如果是这俩就可以直接退出
    {
        return false;
    }
    for (int i = 2; i < n / 2; i++)//从0扫描到一半,n/2即可
    {
        if (n % i == 0)//如果其中有整除的说明就不是质数
        {
            return false;
        }
    }
    return true;
}

template <typename T, typename Hash>
int HashTable<T, Hash>::get_prime(int n)//表示获得一个比n大的质数
{
    if (n % 2 == 0)//一开始能被2整除就肯定不是
    {
        n++;
    }
    while (!check_prime(n))
    {
        n += 2;//然后之后对这个奇数+=2直到找到为止
    }
    return n;
}

template <typename T, typename Hash>
typename HashTable<T, Hash>::Node ** HashTable<T, Hash>::buckets_create(int bucket_count)
{
    auto buckets = new Node *[bucket_count];//这边是new出二级指针,即指针数组
    std::memset(buckets, 0, sizeof(Node *) * bucket_count);
    return buckets;
}

template <typename T, typename Hash>
bool HashTable<T, Hash>::buckets_insert(Node ** buckets, int bucket_count, const T & key)
{
    size_t hashcode = m_hash(key);
    int slot = hashcode % bucket_count;//计算到对应的桶
    auto node = buckets[slot];
    if (node == nullptr)//还没被插入就直接插入
    {
        buckets[slot] = new Node(key, hashcode);
        return true;
    }

    auto curr = node;
    while (curr->m_next != nullptr)//否则找到对应的链表位置插入
    {
        if (curr->m_key == key)//如果已经存在了就返回失败
            return false;
        curr = curr->m_next;
    }
    curr->m_next = new Node(key, hashcode);
    return true;
}

template <typename T, typename Hash>
bool HashTable<T, Hash>::buckets_remove(Node ** buckets, int bucket_count, const T & key)
{
    if (buckets == nullptr)
        return false;
    size_t hashcode = m_hash(key);
    int slot = hashcode % bucket_count;
    auto node = buckets[slot];
    if (node == nullptr)
        return false;

    if (node->m_key == key)
    {
        buckets[slot] = node->m_next;
        delete node;
        return true;
    }

    auto prev = node;//记录前驱节点
    auto curr = node->m_next;
    while (curr != nullptr)
    {
        if (curr->m_key == key)
            break;
        prev = curr;
        curr = curr->m_next;
    }

    if (curr == nullptr)
        return false;

    prev->m_next = curr->m_next;//找到了就把前驱指向待删除的后继
    delete curr;
    return true;
}

template <typename T, typename Hash>
typename HashTable<T, Hash>::Node * HashTable<T, Hash>::buckets_search(Node ** buckets, int bucket_count, const T & key)
{
    if (buckets == nullptr)
        return nullptr;
    size_t hashcode = m_hash(key);
    int slot = hashcode % bucket_count;
    auto node = buckets[slot];
    while (node != nullptr)//就是链表查找而已
    {
        if (node->m_key == key)
            return node;
        node = node->m_next;
    }
    return nullptr;
}

template <typename T, typename Hash>
void HashTable<T, Hash>::buckets_migrate(Node ** buckets, int bucket_count, Node * node)
{
    if (buckets == nullptr)
        return;
    node->m_next = nullptr;
    auto slot = node->m_code % bucket_count;
    auto curr = buckets[slot];
    if (curr == nullptr)
    {
        buckets[slot] = node;
        return;
    }
    while (curr->m_next != nullptr)
    {
        if (curr->m_key == node->m_key)
            return;
        curr = curr->m_next;
    }
    curr->m_next = node;
}

template <typename T, typename Hash>
void HashTable<T, Hash>::buckets_destroy(Node ** buckets, int bucket_count)
{
    if (buckets == nullptr)
        return;
    for (int i = 0; i < bucket_count; i++)
    {
        auto node = buckets[i];
        while (node != nullptr)
        {
            auto temp = node->m_next;//就是遍历每个节点然后删除而已
            delete node;
            node = temp;
        }
    }
}