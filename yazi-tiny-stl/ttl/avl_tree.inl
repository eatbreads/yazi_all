template <typename T>
AVLTree<T>::AVLTree() : BSTree<T>() {}

template <typename T>
AVLTree<T>::~AVLTree() {}

template <typename T>
TreeNode<T> * AVLTree<T>::create_node(const T & key)//这个也是虚函数,虽然内部和BS_Tree一样
{                                                   //但是node其实是AVL的node
    auto node = new Node(key);
    this->m_size++;
    return node;
}

template <typename T>
void AVLTree<T>::delete_node(TreeNode<T> * node)//同上
{
    this->m_size--;
    delete node;
}
 
template <typename T>
void AVLTree<T>::insert(const T & key)
{
    this->m_root = insert(this->m_root, key);
}

template <typename T>
void AVLTree<T>::remove(const T & key)
{
    this->m_root = remove(this->m_root, key);
}
 
template <typename T>
TreeNode<T> * AVLTree<T>::insert(TreeNode<T> * root, const T & key)
{
    root = BSTree<T>::insert(root, key);
    return insert_fix(root);
}

template <typename T>
TreeNode<T> * AVLTree<T>::remove(TreeNode<T> * root, const T & key)
{
    root = BSTree<T>::remove(root, key);
    return remove_fix(root);
}

template <typename T>
int AVLTree<T>::height(TreeNode<T> * node) const
{
    if (node == nullptr)
        return 0;
    return ((Node *)node)->m_height;
}

template <typename T>
TreeNode<T> * AVLTree<T>::left_rotate(TreeNode<T> * node)
{
    auto x = BSTree<T>::left_rotate(node);  //旋转完之后更新高度,只有原根节点和被换上来的现根节点要改高度
    ((Node *)node)->m_height = max(height(node->m_left), height(node->m_right)) + 1;//这边要进行强转,否则子类定位不到height的数据
    ((Node *)x)->m_height = max(height(x->m_left), height(x->m_right)) + 1;
    return x;
}

template <typename T>
TreeNode<T> * AVLTree<T>::right_rotate(TreeNode<T> * node)
{
    auto x = BSTree<T>::right_rotate(node);
    ((Node *)node)->m_height = max(height(node->m_left), height(node->m_right)) + 1;
    ((Node *)x)->m_height = max(height(x->m_left), height(x->m_right)) + 1;
    return x;
}

template <typename T>
int AVLTree<T>::get_balance_factor(TreeNode<T> * node)
{
    if (node == nullptr)
        return 0;
    return height(node->m_left) - height(node->m_right);
}

template <typename T>
TreeNode<T> * AVLTree<T>::rebalance(TreeNode<T> * root)
{
    if (root == nullptr)
        return nullptr;

    // update the balance factor of each node and balance the tree
    ((Node *)root)->m_height = max(height(root->m_left), height(root->m_right)) + 1;
    int factor = get_balance_factor(root);
    if (factor > 1)
    {
        if (get_balance_factor(root->m_left) < 0)//平衡因子大于0,即左边比较高,就应该进行左旋
            root->m_left = left_rotate(root->m_left);
        return right_rotate(root);
    }
    if (factor < -1)
    {
        if (get_balance_factor(root->m_right) > 0)
            root->m_right = right_rotate(root->m_right);//反之应该进行右旋
        return left_rotate(root);
    }
    return root;
}

template <typename T>
TreeNode<T> * AVLTree<T>::insert_fix(TreeNode<T> * root)
{
    return rebalance(root);
}

template <typename T>
TreeNode<T> * AVLTree<T>::remove_fix(TreeNode<T> * root)
{
    return rebalance(root);
}

template <typename T>
bool AVLTree<T>::add(const T & key)
{
    auto node = BSTree<T>::add_raw(key);
    if (node == nullptr)
        return false;

    while (node != nullptr)
    {
        node = insert_fix(node);
        if (node->m_parent == nullptr)
        {
            this->m_root = node;
        }
        node = node->m_parent;
    }
    return true;
}

template <typename T>
bool AVLTree<T>::del(const T & key)
{
    auto node = BSTree<T>::del_raw(key);
    if (node == nullptr)
        return false;

    TreeNode<T> * repl = nullptr;
    if (node->m_left != nullptr && node->m_right == nullptr)
        repl = node->m_left;
    if (node->m_left == nullptr && node->m_right != nullptr)
        repl = node->m_right;
    if (repl != nullptr)
        repl->m_parent = node->m_parent;
    if (node->m_parent == nullptr)
        this->m_root = repl;
    else
    {
        if (node == node->m_parent->m_left)
            node->m_parent->m_left = repl;
        else
            node->m_parent->m_right = repl;
    }//这边上面其实都是BS_Tree的del

    auto root = node->m_parent;//区别就是这边要拿到待删除节点的父节点
    delete_node(node);
    while (root != nullptr)//然后递归上去修复节点
    {
        root = remove_fix(root);
        if (root->m_parent == nullptr)
        {
            this->m_root = root;
        }
        root = root->m_parent;
    }
    return true;
} 