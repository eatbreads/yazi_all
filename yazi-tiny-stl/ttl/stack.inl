template <typename T, typename Container>
Stack<T, Container>::Stack() {}

template <typename T, typename Container>
Stack<T, Container>::~Stack() {}

template <typename T, typename Container>
void Stack<T, Container>::push(const T & value)
{
    m_container.push_back(value);
}

template <typename T, typename Container>
void Stack<T, Container>::pop()
{
    m_container.pop_back();
}

template <typename T, typename Container>
T & Stack<T, Container>::top()
{
    return m_container.back();
}

template <typename T, typename Container>
const T & Stack<T, Container>::top() const
{
    return m_container.back();
}

template <typename T, typename Container>
int Stack<T, Container>::size() const
{
    return m_container.size();
}

template <typename T, typename Container>
bool Stack<T, Container>::empty() const
{
    return m_container.empty();
}

template <typename T, typename Container>
void Stack<T, Container>::swap(Stack<T, Container> & other)
{
    m_container.swap(other.m_container);
}

template <typename T, typename Container>
void Stack<T, Container>::show() const
{
    m_container.show();
}
