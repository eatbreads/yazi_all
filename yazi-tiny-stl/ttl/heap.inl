template <typename T, typename Container, typename Compare>
Heap<T, Container, Compare>::Heap() {}

template <typename T, typename Container, typename Compare>
Heap<T, Container, Compare>::~Heap() {}

template <typename T, typename Container, typename Compare>
void Heap<T, Container, Compare>::heapify(int i)//表示堆化,生成堆,i表示对下标为i的非叶子节点执行调整堆
{
    int size = m_container.size();
    int largest = i;//表示应该成为父节点的下标
    int l = 2 * i + 1;//拿到左孩子下标
    int r = 2 * i + 2;//拿到右孩子下标
    if (l < size && m_compare(m_container[largest], m_container[l]))
    {
        largest = l;//如果左更大
    }
    if (r < size && m_compare(m_container[largest], m_container[r]))
    { 
        largest = r;//可能右孩子会比左孩子大,此时就应该是右孩子上来
    }
    if (largest != i)//表示应该被交换
    {
        // swap the value of index i and largest
        T temp = m_container[i];
        m_container[i] = m_container[largest];//叶子节点取代父节点
        m_container[largest] = temp;

    }
}

template <typename T, typename Container, typename Compare>
void Heap<T, Container, Compare>::push(const T & value)
{
    m_container.push_back(value);//直接插到最后面
    int size = m_container.size();
    if (size > 1)
    {//最大的非叶子节点是size/2-1,相当于从右下往左上把父节点全部调整了
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            heapify(i);//执行一次操作都要调整一次堆
        }
    }
}

template <typename T, typename Container, typename Compare>
void Heap<T, Container, Compare>::pop()
{
    int size = m_container.size();
    T temp = m_container[0];
    m_container[0] = m_container[size - 1];
    m_container[size - 1] = temp;//相当于把根节点和右下叶子交换
    m_container.pop_back();//然后执行vector的pop_back

    size = m_container.size();
    if (size > 1)
    {
        for (int i = size / 2 - 1; i >= 0; i--)
        {//然后也是对所有执行生成堆
            heapify(i);
        }
    }
}

template <typename T, typename Container, typename Compare>
const T & Heap<T, Container, Compare>::top() const
{
    return m_container.front();
}

template <typename T, typename Container, typename Compare>
bool Heap<T, Container, Compare>::empty() const
{
    return m_container.empty();
}

template <typename T, typename Container, typename Compare>
int Heap<T, Container, Compare>::size() const
{
    return m_container.size();
}

template <typename T, typename Container, typename Compare>
void Heap<T, Container, Compare>::swap(Heap<T, Container, Compare> & other)
{
    m_container.swap(other.m_container);
}
g
template <typename T, typename Container, typename Compare>
void Heap<T, Container, Compare>::show() const
{
    m_container.show();
}