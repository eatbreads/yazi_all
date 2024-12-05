template <typename T>
RBTree<T>::RBTree() : BSTree<T>() {}

template <typename T>
RBTree<T>::~RBTree() {}

template <typename T>
TreeNode<T> * RBTree<T>::create_node(const T & key)
{
    auto node = new Node(key);
    if (this->m_root == nullptr)
    {
        set_color(node, 'B');//这边长得和之前的也差不多,但是要设置颜色
    }
    this->m_size++;
    return node;
}

template <typename T>
void RBTree<T>::delete_node(TreeNode<T> * node)
{
    this->m_size--;
    delete node;
}

template <typename T>
void RBTree<T>::insert(const T & key)
{
    this->m_root = insert(this->m_root, key);
}

template <typename T>
void RBTree<T>::remove(const T & key)
{
    this->m_root = remove(this->m_root, key);
}

template <typename T>
TreeNode<T> * RBTree<T>::insert(TreeNode<T> * root, const T & key)
{
    root = BSTree<T>::insert(root, key);//这个地方是一个递归的操作,即每一层都会insert_fix回来
    return insert_fix(root);//每一层都会标记一下下一次回来是否需要修改
}

template <typename T>
TreeNode<T> * RBTree<T>::remove(TreeNode<T> * root, const T & key)
{
    root = BSTree<T>::remove(root, key);
    return remove_fix(root);
}

template <typename T>
bool RBTree<T>::is_color(TreeNode<T> * node, char color)
{
    if (node == nullptr)//空节点是黑节点,由定义决定的
    {
        return color == 'B';
    }
    return ((Node *)node)->m_color == color;
}

template <typename T>
void RBTree<T>::set_color(TreeNode<T> * node, char color)
{
    if (node != nullptr)
    {
        ((Node *)node)->m_color = color;
    }
}

template <typename T>
TreeNode<T> * RBTree<T>::insert_fix(TreeNode<T> * root)
{
    // perform rotations
    if (m_l)
    {
        root = this->left_rotate(root);
        set_color(root, 'B');
        set_color(root->m_left, 'R');
        m_l = false;
    }
    else if (m_r)
    {
        root = this->right_rotate(root);
        set_color(root, 'B');
        set_color(root->m_right, 'R');  
        m_r = false;
    }
    else if (m_lr)
    {
        root->m_left = this->left_rotate(root->m_left);
        root = this->right_rotate(root);
        set_color(root, 'B');
        set_color(root->m_right, 'R');
        m_lr = false;
    }
    else if (m_rl)
    {
        root->m_right = this->right_rotate(root->m_right);
        root = this->left_rotate(root);
        set_color(root, 'B'); 
        set_color(root->m_left, 'R');
        m_rl = false;
    }

    // flag to check color conflict
    bool flag = false;//这里可能是上面的else一个都没进去,但实际上还是存在着需要修改
    if (is_color(root, 'R') && is_color(root->m_left, 'R'))
    {
        flag = true;
    }
    if (is_color(root, 'R') && is_color(root->m_right, 'R'))
    {
        flag = true;
    }//flag检测当前节点是否应该旋转,但是是会在下一次递归的时候被修改

    // handle color conflicts
    if (flag)//如果需要进行旋转或者着色等
    {
        if (root->m_parent->m_left == root)//判断待插入节点是父节点的左子树还是右子树
        {//ps:是左孩子就意味着肯定是ll型或者lr型(第一下是往左)
            if (is_color(root->m_parent->m_right, 'B'))//如果表兄是黑色,空节点也是黑
            {
                if (is_color(root->m_left, 'R'))
                    m_r = true;     //就是最简单的一条左边斜线,需要右旋
                else if (is_color(root->m_right, 'R'))
                    m_lr = true;//这就是lr了,左旋然后右旋
            }
            else//这边是表兄节点是红色,只需要染色而已
            {
                if (root->m_parent != this->m_root)//讨论一下不是根节点的情况
                    set_color(root->m_parent, 'R');//父节点染成红
                set_color(root, 'B');               //当前节点和表兄节点染成黑
                set_color(root->m_parent->m_right, 'B');
            }
        }
        else//表示插入节点是父节点的右子树(和上面镜像,基本一样)
        {
            if (is_color(root->m_parent->m_left, 'B'))
            {
                if (is_color(root->m_right, 'R'))
                    m_l = true;
                else if (is_color(root->m_left, 'R'))
                    m_rl = true;
            }
            else
            {
                if (root->m_parent != this->m_root)
                    set_color(root->m_parent, 'R');
                set_color(root, 'B');
                set_color(root->m_parent->m_left, 'B');
            }
        }
    }
    return root;
}

template <typename T>
TreeNode<T> * RBTree<T>::remove_fix(TreeNode<T> * root)
{
    // 备注：递归删除暂未实现，请查看非递归删除(del函数)
    return root;
}

template <typename T>
TreeNode<T> * RBTree<T>::del_fix(TreeNode<T> * node)
{
    TreeNode<T> * x = node;
    while (x != this->m_root && is_color(x, 'B'))
    {
        if (x == x->m_parent->m_left)
        {
            auto s = x->m_parent->m_right;
            if (is_color(s, 'R'))
            {
                // case 3.1
                set_color(s, 'B');
                set_color(x->m_parent, 'R');
                this->left_rotate(x->m_parent);
                s = x->m_parent->m_right;
            }
            if (is_color(s->m_left, 'B') && is_color(s->m_right, 'B'))
            {
                // case 3.2
                set_color(s, 'R');
                x = x->m_parent;
            }
            else
            {
                if (is_color(s->m_left, 'R'))
                {
                    // case 3.4
                    set_color(s->m_left, 'B');
                    set_color(s, 'R');
                    this->right_rotate(s);
                    s = x->m_parent->m_right;
                }
                // case 3.3
                set_color(s, ((Node *)x->m_parent)->m_color);
                set_color(x->m_parent, 'B');
                set_color(s->m_right, 'B');
                this->left_rotate(x->m_parent);
                x = this->m_root;
            }
        }
        else
        {
            // mirror situation
            auto s = x->m_parent->m_left;
            if (is_color(s, 'R'))
            {
                // case 3.1
                set_color(s, 'B');
                set_color(x->m_parent, 'R');
                this->right_rotate(x->m_parent);
                s = x->m_parent->m_left;
            }
            if (is_color(s->m_left, 'B') && is_color(s->m_right, 'B'))
            {
                // case 3.2
                set_color(s, 'R');
                x = x->m_parent;
            }
            else
            {
                if (is_color(s->m_right, 'R'))
                {
                    // case 3.4
                    set_color(s->m_right, 'B');
                    set_color(s, 'R');
                    this->left_rotate(s);
                    s = x->m_parent->m_left;
                }
                // case 3.3
                set_color(s, ((Node *)x->m_parent)->m_color);
                set_color(x->m_parent, 'B');
                set_color(s->m_left, 'B');
                this->right_rotate(x->m_parent);
                x = this->m_root;
            }
        }
    }
    set_color(x, 'B');
    return x;
}

template <typename T>
bool RBTree<T>::add(const T & key)
{
    auto node = BSTree<T>::add_raw(key);
    while (node != nullptr)
    {
        node = insert_fix(node);
        if (node->m_parent == nullptr)//过程中可能有其他节点被设置为根节点
        {
            this->m_root = node;//更新根节点
        }
        node = node->m_parent;
    }
    return true;
}

template <typename T>
bool RBTree<T>::del(const T & key)
{
    auto node = BSTree<T>::del_raw(key);
    if (node == nullptr)
        return false;

    if (node->m_left != nullptr || node->m_right != nullptr)
    {
        auto repl = (node->m_left != nullptr) ? node->m_left : node->m_right;
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
        }
        set_color(repl, 'B');
        this->delete_node(node);
        return true;
    }

    // if the node is red and has no child
    if (is_color(node, 'R'))
    {
        if (node == node->m_parent->m_left)
            node->m_parent->m_left = nullptr;
        else
            node->m_parent->m_right = nullptr;
        this->delete_node(node);
        return true;
    }

    if (node->m_parent == nullptr)
    {
        // delete the last root node
        this->delete_node(node);
        this->m_root = nullptr;
        return true;
    }

    // if the node is black and has no child
    del_fix(node);
    if (node->m_parent != nullptr)
    {
        if (node == node->m_parent->m_left)
            node->m_parent->m_left = nullptr;
        else
            node->m_parent->m_right = nullptr;
    }
    delete_node(node);
    return true;
}