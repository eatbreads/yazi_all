template <typename T>
BSTree<T>::BSTree() : Tree<T>() {}

template <typename T>
BSTree<T>::~BSTree() {}

template <typename T>
TreeNode<T> * BSTree<T>::create_node(const T & key)
{
    auto node = new Node(key);
    this->m_size++;
    return node;
}

template <typename T>
void BSTree<T>::delete_node(TreeNode<T> * node)
{
    this->m_size--;
    delete node;
}

template <typename T> 
void BSTree<T>::insert(const T & key)
{
    this->m_root = insert(this->m_root, key);
}

template <typename T>
void BSTree<T>::remove(const T & key)
{
    this->m_root = remove(this->m_root, key);
}

template <typename T>
TreeNode<T> * BSTree<T>::insert(TreeNode<T> * root, const T & key)//这个函数会插入之后,并且返回插入后的根节点
{
    if (root == nullptr)
    {
        return create_node(key);
    }
    if (root->m_key > key)//根据当前值决定递归哪一个
    {
        root->m_left = insert(root->m_left, key);
        root->m_left->m_parent = root;      //这边进行节点的更新处理
    }
    else if (root->m_key < key)
    {
        root->m_right = insert(root->m_right, key);
        root->m_right->m_parent = root;
    }
    else
    {
        return root;
    }
    return root;
}

template <typename T>
TreeNode<T> * BSTree<T>::remove(TreeNode<T> * root, const T & key)//这个函数会返回更新之后的树的根节点
{
    if (root == nullptr)
        return nullptr;
    if (root->m_key > key)//根据当前root来决定往左右递归进去
    {
        root->m_left = remove(root->m_left, key);//拿到根节点,并且把它赋值给left
        if (root->m_left != nullptr)
            root->m_left->m_parent = root;//然后记得处理对应的节点指向
    }
    else if (root->m_key < key)
    {
        root->m_right = remove(root->m_right, key);
        if (root->m_right != nullptr)
            root->m_right->m_parent = root;
    }
    else//这边表示当前节点就是要删除的节点
    {
        if (root->m_left == nullptr)//若没有左子树
        {
            auto r = root->m_right;
            if (r != nullptr)
                r->m_parent = root->m_parent;//把右子树的父亲更新为当前节点的父亲(表示当前节点可以被删了)
            delete_node(root);              //这里感觉其实不用更新,因为上面递归回去会更新
            return r;
        }
        else if (root->m_right == nullptr)//若没有右子树
        {
            auto l = root->m_left;
            if (l != nullptr)
                l->m_parent = root->m_parent;
            delete_node(root);
            return l;
        }
        else//若都有,就通过赋值的方法统一使用上面的删除操作(感觉这里效率可以优化)
        {   //但好像其实不行,因为他要返回一个节点,如果两个子树都有的话,删除当前之后就不知道返回谁了
            // if the node has two child
            auto node = root->successor();
            root->m_key = node->m_key;
            root->m_right = remove(root->m_right, node->m_key);
        }
    }
    return root;
}

template <typename T>
TreeNode<T> * BSTree<T>::left_rotate(TreeNode<T> * node)
{
    auto p = node->m_parent;
    auto y = node->m_right;
    auto B = y->m_left;
    y->m_left = node;
    node->m_parent = y;
    node->m_right = B;
    if (B != nullptr)
        B->m_parent = node;
    y->m_parent = p;
    if (p == nullptr)
    {
        this->m_root = y;
    }
    else
    {
        if (p->m_left == node)
            p->m_left = y;
        else
            p->m_right = y;
    }
    return y;
}

template <typename T>
TreeNode<T> * BSTree<T>::right_rotate(TreeNode<T> * node)
{
    auto p = node->m_parent;
    auto x = node->m_left;
    auto y = x->m_right;
    x->m_right = node;
    node->m_parent = x;
    node->m_left = y;//右旋就是反过来
    if (y != nullptr)
        y->m_parent = node;
    x->m_parent = p;
    if (p == nullptr)
    {
        this->m_root = x;
    }
    else
    {
        if (p->m_left == node)
            p->m_left = x;
        else
            p->m_right = x;
    }
    return x;
}

template <typename T>
TreeNode<T> * BSTree<T>::add_raw(const T & key)//这边定义了原始函数,且不是虚函数,这样降低耦合度
{
    auto root = this->m_root;
    TreeNode<T> * parent = nullptr;
    while (root != nullptr)//这个函数会一直遍历到叶子节点(root != nullptr)
    {
        parent = root;
        if (root->m_key == key)//如果里面已经存在了,就返回空即可
            return nullptr;
        if (key < root->m_key)
            root = root->m_left;
        else
            root = root->m_right;
    }
    auto node = create_node(key);
    if (this->m_root == nullptr)//整个树为空
    {
        this->m_root = node;
        return node;
    }
    if (key < parent->m_key)    //然后调整节点指向,因为他是叶子,所以不需要处理它的子树
    {
        parent->m_left = node;
        node->m_parent = parent;
    }
    else
    {
        parent->m_right = node;
        node->m_parent = parent;
    }
    return node;
}

template <typename T>
TreeNode<T> * BSTree<T>::del_raw(const T & key)//这个函数其实没有删除东西,只是为了找到值
{
    auto root = this->m_root;
    while (root != nullptr)//这个while最终会定位到要删除的节点
    {
        if (root->m_key > key)
            root = root->m_left;
        else if (root->m_key < key)
            root = root->m_right;
        else
            break;
    }

    if (root == nullptr)//没有找到
    {
        // not found
        return nullptr;
    }

    if (root->m_left != nullptr && root->m_right != nullptr)
    {
        // if the node has two child, find the successor
        auto node = root->successor();
        root->m_key = node->m_key;//这里好巧妙,就是找到后继节点,然后交换一下而已
        root = node;              //这里其实没有交换节点,只是交换值
    }                             //然后root变成了底下那个叶子(也不一定是叶子)
    return root;
}

template <typename T>
bool BSTree<T>::add(const T & key)//这样重写虚函数的时候就直接调用原始函数即可,就不会把虚函数写的那么复杂
{
    auto node = add_raw(key);
    if (node == nullptr)
        return false;
    return true;
}

template <typename T>
bool BSTree<T>::del(const T & key)
{
    auto node = del_raw(key);
    if (node == nullptr)
        return false;

    TreeNode<T> * repl = nullptr;//现在要执行处理这个叶子节点,这个repl会被赋值为待处理节点的孩子节点
    if (node->m_left != nullptr && node->m_right == nullptr)//只有左节点(但是好像不存在,左节点一定会是上面那个函数后继节点)
        repl = node->m_left;
    if (node->m_left == nullptr && node->m_right != nullptr)//只有有右节点
        repl = node->m_right;
    if (repl != nullptr)
        repl->m_parent = node->m_parent;//相当于越过这个待删除节点
    if (node->m_parent == nullptr)//表示根节点被删了
        this->m_root = repl;
    else//如果不是根节点被删了
    {
        if (node == node->m_parent->m_left)//这条语句即判断node节点是否为左节点
            node->m_parent->m_left = repl;  //是就处理parent的left,把它指到repl
        else
            node->m_parent->m_right = repl;
    }
    delete_node(node);
    return true;
}