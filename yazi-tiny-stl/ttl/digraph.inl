int Digraph::s_count = 0;

Digraph::Digraph()
{
    /* 备注:
     * 创建目录: dot文件和 png文件存放目录的创建
     * 这里使用了我自己写的一个文件目录操作库
     */
    Directory dot_dir("../digraph/dot/");
    if (!dot_dir.create())
    {
        std::cerr << "创建目录失败: " << dot_dir.path() << std::endl;
        return;
    }

    Directory png_dir("../digraph/png/");
    if (!png_dir.create())
    {
        std::cerr << "创建目录失败: " << png_dir.path() << std::endl;
        return;
    }
}

void Digraph::delay(int milliseconds)
{
    m_delay = milliseconds;
}

void Digraph::draw_before()
{
    /*
     * 备注:
     * dot 格式文件是文本文件，用来描述生成的图形
     * png 格式文件是图片文件，实际的图形文件
     * 这里绘图用到了一个工具: graphviz
     * graphviz 官方网站: https://graphviz.org/
     * graphviz 在线工具: https://sketchviz.com/new
     * graphviz 使用手册: https://graphviz.readthedocs.io/en/stable/examples.html
     * graphviz 作为辅助工具，用来会制各个数据结构的图形，方便理解
     */
    string count;
    if (s_count < 10)
        count = "0" + std::to_string(s_count);
    else
        count = std::to_string(s_count);
    s_count++;

    File dot_file("../digraph/dot/digraph" + count + ".dot");
    m_dot_file = dot_file.path();

    File png_file("../digraph/png/digraph" + count + ".png");
    m_png_file = png_file.path();
}

void Digraph::draw_after()
{
    /*
     * 备注:
     * 这里是调用 C 语言的 system 函数来打开一个进程，用来执行命令
     * 不同系统可能会有差异，下面是以 windows 系统为例
     * 如果换成 mac 系统可能会需要调整
     */
    string dot_cmd = "dot -Tpng " + m_dot_file + " -o " + m_png_file;
    std::cout << dot_cmd << std::endl;
    system(dot_cmd.c_str());        // 由 dot 格式生成 png 图片
    system(m_png_file.c_str());     // 调用系统的进程打开 png 图片
    sleep();                        // 延迟一会，文件打开太快了受不了
}

void Digraph::sleep()
{
    Time::sleep(m_delay);
}

string Digraph::ptr2str(void * ptr)
{
    return std::to_string((long long)ptr);
}

template <typename T, int N>
void Digraph::draw(Array<T, N> & a)
{
    draw_before();

    std::ofstream ofs(m_dot_file);
    ofs << "digraph {" << std::endl;
    ofs << "rankdir=LR;" << std::endl;
    ofs << "node[shape=record, width=10, height=1, fontsize=24];" << std::endl;
    ofs << "subgraph cluster_array {" << std::endl;
    ofs << "label=\"array : size = " << a.size() << "\";" << std::endl;
    ofs << "pencolor=white;" << std::endl;
    ofs << "node0[label=\"{";
    for (int i = 0; i < N; i++)
    {
        if (i != 0)
        {
            ofs << "|";
        }
        ofs << a[i];
    }
    ofs << "}\"];" << std::endl;
    ofs << "}}" << std::endl;
    ofs.flush();
    ofs.close();

    draw_after();
}

template <typename T>
void Digraph::draw(Vector<T> & v)
{
    draw_before();

    std::ofstream ofs(m_dot_file);
    ofs << "digraph {" << std::endl;
    ofs << "rankdir=LR;" << std::endl;
    ofs << "node[shape=record, width=10, height=1 fontsize=24];" << std::endl;
    ofs << "subgraph cluster_vector {" << std::endl;
    ofs << "label=\"vector : size = " << v.size() << ", capacity = " << v.capacity() << "\";" << std::endl;
    ofs << "pencolor=white;" << std::endl;
    if (!v.empty())
    {
        ofs << "node0[label=\"{";
        for (int i = 0; i < v.capacity(); i++)
        {
            if (i != 0)
            {
                ofs << "|";
            }
            if (i < v.size())
            {
                ofs << v[i];
            }
        }
        ofs << "}\"];" << std::endl;
    }
    ofs << "}}" << std::endl;
    ofs.flush();
    ofs.close();

    draw_after();
}

template <typename T>
void Digraph::draw(List<T> & l)
{
    draw_before();

    std::ofstream ofs(m_dot_file);
    ofs << "digraph {" << std::endl;
    ofs << "rankdir=LR;" << std::endl;
    ofs << "node[shape=circle fontsize=24 width=1 height=1];" << std::endl;
    ofs << "edge[minlen=2];" << std::endl;
    ofs << "subgraph cluster_list {" << std::endl;
    ofs << "label=\"list : size = " << l.size() << "\";" << std::endl;
    ofs << "pencolor=white;" << std::endl;
    if (l.size() == 1)
    {
        ofs << *(l.begin()) << ";" << std::endl;
    }
    else if (l.size() > 1)
    {
        for (auto it = l.begin(); it != l.end(); ++it)
        {
            if (it + 1 != l.end())
            {
                ofs << *it << " -> " << *(it + 1) << "[xlabel=\"next\"];" << std::endl;
            }
        }
        for (auto it = l.rbegin(); it != l.rend(); ++it)
        {
            if (it + 1 != l.rend())
            {
                ofs << *it << " -> " << *(it + 1) << "[xlabel=\"prev\"];" << std::endl;
            }
        }
    }
    ofs << "}}" << std::endl;
    ofs.flush();
    ofs.close();

    draw_after();
}

template <typename T>
void Digraph::draw(ForwardList<T> & l)
{
    draw_before();

    std::ofstream ofs(m_dot_file);
    ofs << "digraph {" << std::endl;
    ofs << "rankdir=LR;" << std::endl;
    // 设置节点属性
    ofs << "node[shape=circle fontsize=24];" << std::endl;
    ofs << "edge[minlen=2];" << std::endl;
    ofs << "null[shape=plaintext label=\"null\" fillcolor=white];" << std::endl;
    ofs << "subgraph cluster_forward_list {" << std::endl;
    ofs << "label=\"forward_list : size = " << l.size() << "\";" << std::endl;
    ofs << "labelfontsize=28;" << std::endl;
    ofs << "pencolor=white;" << std::endl;
    for (auto it = l.begin(); it != l.end(); ++it)
    {
        if (it + 1 != l.end())
        {
            ofs << *it << " -> " << *(it + 1) << "[xlabel=\"next\"];" << std::endl;
        }
        else
        {
            ofs << *it << " -> null[xlabel=\"next\"];" << std::endl;
        }
    }
    ofs << "}}" << std::endl;
    ofs.flush();
    ofs.close();

    draw_after();
}

template <typename T, typename Container>
void Digraph::draw(Stack<T, Container> & s)
{
    draw(s.m_container);
}

template <typename T, typename Container>
void Digraph::draw(Queue<T, Container> & q)
{
    draw(q.m_container);
}

template <typename T>
void Digraph::draw(Heap<T> & h)
{
    draw(h.m_container);
}

template <typename T, int N>
void Digraph::draw(Deque<T, N> & d)
{
    draw_before();

    std::ofstream ofs(m_dot_file);
    ofs << "digraph {" << std::endl;
    ofs << "rankdir=LR;" << std::endl;
    ofs << "node[shape=record];" << std::endl;
    ofs << "edge[minlen=2];" << std::endl;
    ofs << "subgraph cluster_deque {" << std::endl;
    ofs << "label=\"deque : size = " << d.size() << "\";" << std::endl;
    ofs << "pencolor=white;" << std::endl;
    ofs << "node[width=1 height=1];" << std::endl;
    if (!d.empty())
    {
        ofs << "nodes [fillcolor=gray90 style=filled label=\"";
        for (int i = 0; i < d.m_nodes.size(); i++)
        {
            if (i != 0)
            {
                ofs << "|";
            }
            ofs << "<f" << i << "> " << i;
        }
        ofs << "\" xlabel=\"array\"];" << std::endl;
        ofs << "node[width=5 height=.5];" << std::endl;
        for (int i = 0; i < d.m_nodes.size(); i++)
        {
            ofs << "nodes" << i << " [label=\"{";
            DequeNode<T, N> * node = d.m_nodes[i];
            for (int k = 0; k < N; k++)
            {
                if (k != 0)
                {
                    ofs << "|";
                }
                if (k < node->m_head || k >= node->m_tail)
                {
                    ofs << "<ff" << k << ">";
                }
                else
                {
                    ofs << "<ff" << k << "> " << node->m_data[k];
                }
            }
            ofs << "}\" xlabel=\"array\"];" << std::endl;
        }

        for (int i = 0; i < d.m_nodes.size(); i++)
        {
            ofs << "nodes:f" << i << ":e -> nodes" << i << ":ff0:w;" << std::endl;
        }
    }
    ofs << "}}" << std::endl;
    ofs.flush();
    ofs.close();

    draw_after();
}

template <typename T, int max_level>
void Digraph::draw(SkipList<T, max_level> & s)
{
    draw_before();

    std::ofstream ofs(m_dot_file);
    ofs << "digraph {" << std::endl;
    ofs << "rankdir=\"LR\";" << std::endl;
    ofs << "node[shape=record fillcolor=gray90 style=filled fontsize=24];" << std::endl;
    ofs << "subgraph cluster_skip_list {" << std::endl;
    ofs << "label=\"skip list : size = " << s.size() << ", level = " << s.m_level << ", max_level = " << max_level << "\";" << std::endl;
    ofs << "pencolor=white;" << std::endl;
    if (!s.empty())
    {
        SkipListNode<T> * node = s.m_head;
        while (node != nullptr)
        {
            if (node == s.m_head)
            {
                ofs << "nodes" << ptr2str(node) << "[label=\"{head|{";
            }
            else
            {
                ofs << "nodes" << ptr2str(node) << "[label=\"{" << node->m_value << "|{";
            }
            for (int i = 0; i < node->m_level; i++)
            {
                if (i != 0)
                {
                    ofs << "|";
                }
                ofs << "<f" << i << ">";
            }
            ofs << "}}\"];" << std::endl;
            node = node->m_forward[0];
        }
        ofs << "null" << "[label=\"{null|{";
        for (int i = 0; i < max_level; i++)
        {
            if (i != 0)
            {
                ofs << "|";
            }
        }
        ofs << "}}\"];" << std::endl;

        node = s.m_head;
        while (node != nullptr)
        {
            for (int i = 0; i < node->m_level; i++)
            {
                auto ptr = node->m_forward[i];
                if (ptr != nullptr)
                {
                    ofs << "nodes" << ptr2str(node) << ":f" << i << " -> nodes" << std::to_string((long long)ptr) << ";" << std::endl;
                }
                else
                {
                    ofs << "nodes" << ptr2str(node) << ":f" << i << " -> null;" << std::endl;
                }
            }
            node = node->m_forward[0];
        }
    }
    ofs << "}}" << std::endl;
    ofs.flush();
    ofs.close();

    draw_after();
}

template <typename T>
void Digraph::draw(BSTree<T> & t)
{
    draw_before();

    std::ofstream ofs(m_dot_file);
    ofs << "digraph {" << std::endl;
    ofs << "rankdir=TB;" << std::endl;
    ofs << "node[shape=circle fillcolor=gray90 style=filled fontsize=24];" << std::endl;
    ofs << "subgraph cluster_tree {" << std::endl;
    ofs << "label=\"binary search tree : size = " << t.size() << "\";" << std::endl;
    ofs << "pencolor=white;" << std::endl;

    auto root = (BSTreeNode<T> *)t.m_root;
    draw_tree_edge(ofs, root);
    draw_tree_node(ofs, root);

    ofs << "}}" << std::endl;
    ofs.flush();
    ofs.close();

    draw_after();
}

template <typename T>
void Digraph::draw(AVLTree<T> & t)
{
    draw_before();

    std::ofstream ofs(m_dot_file);
    ofs << "digraph {" << std::endl;
    ofs << "rankdir=TB;" << std::endl;
    ofs << "node[shape=circle fillcolor=gray90 style=filled fontsize=24];" << std::endl;
    ofs << "subgraph cluster_tree {" << std::endl;
    ofs << "label=\"avl tree : size = " << t.size() << "\";" << std::endl;
    ofs << "pencolor=white;" << std::endl;

    auto root = (AVLTreeNode<T> *)t.m_root;
    draw_tree_edge(ofs, root);
    draw_tree_node(ofs, root);

    ofs << "}}" << std::endl;
    ofs.flush();
    ofs.close();

    draw_after();
}

template <typename T>
void Digraph::draw(RBTree<T> & t)
{
    draw_before();

    std::ofstream ofs(m_dot_file);
    ofs << "digraph {" << std::endl;
    ofs << "rankdir=TB;" << std::endl;
    ofs << "node[shape=circle fillcolor=lightgray style=filled fontsize=24];" << std::endl;
    ofs << "subgraph cluster_tree {" << std::endl;
    ofs << "label=\"red black tree : size = " << t.size() << "\";" << std::endl;
    ofs << "pencolor=white;" << std::endl;

    auto root = (RBTreeNode<T> *)t.m_root;
    draw_tree_edge(ofs, root);
    draw_tree_node(ofs, root);

    ofs << "}}" << std::endl;
    ofs.flush();
    ofs.close();

    draw_after();
}

template <typename T, int t>
void Digraph::draw(BTree<T, t> & tree)
{
    draw_before();

    std::ofstream ofs(m_dot_file);
    ofs << "digraph {" << std::endl;
    ofs << "rankdir=TB;" << std::endl;
    ofs << "node[shape=record fillcolor=gray90 style=filled fontsize=24];" << std::endl;
    ofs << "edge[minlen=2];" << std::endl;
    ofs << "subgraph cluster_tree {" << std::endl;
    ofs << "label=\"btree :" << " t = " << t << ", size = " << tree.size() << "\";" << std::endl;
    ofs << "pencolor=white;" << std::endl;

    auto root = tree.m_root;
    draw_tree_node(ofs, root);
    draw_tree_edge(ofs, root);

    ofs << "}}";
    ofs.flush();
    ofs.close();

    draw_after();
}

template <typename T, int t>
void Digraph::draw(BBTree<T, t> & tree)
{
    draw_before();

    std::ofstream ofs(m_dot_file);
    ofs << "digraph {" << std::endl;
    ofs << "rankdir=TB;" << std::endl;
    ofs << "node[shape=record fillcolor=gray90 style=filled fontsize=24];" << std::endl;
    ofs << "edge[minlen=2];" << std::endl;
    ofs << "subgraph cluster_tree {" << std::endl;
    ofs << "label=\"bb_tree :" << " t = " << t << ", size = " << tree.size() << "\";" << std::endl;
    ofs << "pencolor=white;" << std::endl;

    auto root = tree.m_root;
    draw_tree_node(ofs, root);
    draw_tree_edge(ofs, root);

    ofs << "}}";
    ofs.flush();
    ofs.close();

    draw_after();
}

template <typename T, typename D, int t>
void Digraph::draw(BPTree<T, D, t> & tree)
{
    draw_before();

    std::ofstream ofs(m_dot_file);
    ofs << "digraph {" << std::endl;
    ofs << "rankdir=TB;" << std::endl;
    // 设置节点属性
    ofs << "node[shape=record fillcolor=gray90 style=filled fontsize=24];" << std::endl;
    ofs << "edge[minlen=2];" << std::endl;
    ofs << "subgraph cluster_tree {" << std::endl;
    ofs << "label=\"b_plus_tree :" << " t = " << t << ", size = " << tree.size() << "\";" << std::endl;
    ofs << "pencolor=white;" << std::endl;

    auto root = tree.m_root;
    draw_tree_node(ofs, root);
    draw_tree_edge(ofs, root);
//    draw_leaf_link(ofs, root);

    ofs << "}}";
    ofs.flush();
    ofs.close();

    draw_after();
}

template <typename T, typename Hash>
void Digraph::draw(HashTable<T, Hash> & table)
{
    draw_before();

    std::ofstream ofs(m_dot_file);
    ofs << "digraph {" << std::endl;
    ofs << "nodesep = .05;" << std::endl;
    ofs << "rankdir=LR;" << std::endl;
    // 设置节点属性
    ofs << "node[shape=record width=0.1 height=0.1];" << std::endl;
    ofs << "subgraph cluster_hash_table {" << std::endl;
    ofs << "label=\"hash_table : size = " << table.size() << ", bucket_count = " << table.bucket_count() << "\";" << std::endl;
    ofs << "pencolor=white;" << std::endl;

    ofs << "node0[label=\"";
    for (int i = 0; i < table.bucket_count(); i++)
    {
        if (i != 0)
        {
            ofs << "|";
        }
        ofs << "<f" << i << ">" << i;
    }
    ofs << "\" width=0.5 height=5];" << std::endl;

    for (int i = 0; i < table.bucket_count(); i++)
    {
        if (table.m_buckets[i] != nullptr)
            draw_hash_bucket_node(ofs, table.m_buckets[i]);
    }

    for (int i = 0; i < table.bucket_count(); i++)
    {
        if (table.m_buckets[i] != nullptr)
            draw_hash_bucket_link(ofs, table.m_buckets[i], i);
    }

    ofs << "}}";
    ofs.flush();
    ofs.close();

    draw_after();
}

template <typename T, typename Hash, typename Container>
void Digraph::draw(HashMap<T, Hash, Container> & m)
{
    draw(m.m_container);
}

template <typename T>
void Digraph::draw_tree_node(std::ofstream & ofs, BSTreeNode<T> * node)
{
    if (node == nullptr)
        return;
    ofs << "node" << ptr2str(node) << "[label=\"" << node->m_key << "\"];" << std::endl;
    draw_tree_node(ofs, (BSTreeNode<T> *)node->m_left);
    draw_tree_node(ofs, (BSTreeNode<T> *)node->m_right);
}

template <typename T>
void Digraph::draw_tree_edge(std::ofstream & ofs, BSTreeNode<T> * node)
{
    static int count = 0;
    if (node == nullptr)
        return;
    if (node->m_left != nullptr)
    {
        ofs << "node" << ptr2str(node) << " -> " << "node" << ptr2str(node->m_left) << ";" << std::endl;
        draw_tree_edge(ofs, (BSTreeNode<T> *)node->m_left);
    }
    else
    {
        ofs << "n" << count << "[style=invis];" << std::endl;
        ofs << "node" << ptr2str(node) << " -> n" << count << "[style=invis];" << std::endl;
        count++;
    }
    ofs << "n" << count << "[style=invis];" << std::endl;
    ofs << "node" << ptr2str(node) << " -> n" << count << "[style=invis];" << std::endl;
    count++;
    if (node->m_right != nullptr)
    {
        ofs << "node" << ptr2str(node) << " -> " << "node" << ptr2str(node->m_right) << ";" << std::endl;
        draw_tree_edge(ofs, (BSTreeNode<T> *)node->m_right);
    }
    else
    {
        ofs << "n" << count << "[style=invis];" << std::endl;
        ofs << "node" << ptr2str(node) << " -> n" << count << "[style=invis];" << std::endl;
        count++;
    }
}

template <typename T>
void Digraph::draw_tree_node(std::ofstream & ofs, AVLTreeNode<T> * node)
{
    draw_tree_node(ofs, (BSTreeNode<T> *)node);
}

template <typename T>
void Digraph::draw_tree_edge(std::ofstream & ofs, AVLTreeNode<T> * node)
{
    draw_tree_edge(ofs, (BSTreeNode<T> *)node);
}

template <typename T>
void Digraph::draw_tree_node(std::ofstream & ofs, RBTreeNode<T> * node)
{
    if (node == nullptr)
        return;
    switch (node->m_color)
    {
        case 'R':
            ofs << "node" << ptr2str(node) << "[label=\"" << node->m_key << "\" fillcolor=red style=filled fontcolor=white];" << std::endl;
            break;
        case 'B':
            ofs << "node" << ptr2str(node) << "[label=\"" << node->m_key << "\" fillcolor=black style=filled fontcolor=white];" << std::endl;
            break;
        default:
            break;
    }
    draw_tree_node(ofs, (RBTreeNode<T> *)node->m_left);
    draw_tree_node(ofs, (RBTreeNode<T> *)node->m_right);
}

template <typename T>
void Digraph::draw_tree_edge(std::ofstream & ofs, RBTreeNode<T> * node)
{
    draw_tree_edge(ofs, (BSTreeNode<T> *)node);
}

template <typename T, int t>
void Digraph::draw_tree_node(std::ofstream & ofs, BTreeNode<T, t> * node)
{
    if (node == nullptr)
        return;
    ofs << "node" << ptr2str(node) << "[label=\"{{";
    for (int i = 0; i < node->m_size; i++)
    {
        if (i != 0)
            ofs << "|";
        ofs << node->m_keys[i];
    }
    ofs << "}|{";
    for (int i = 0; i <= node->m_size; i++)
    {
        if (i != 0)
            ofs << "|";
        ofs << "<f" << i << ">";
    }
    ofs << "}}\"];" << std::endl;

    if (!node->m_leaf)
    {
        for (int i = 0; i < node->m_size + 1; i++)
        {
            draw_tree_node(ofs, node->m_children[i]);
        }
    }
}

template <typename T, int t>
void Digraph::draw_tree_edge(std::ofstream & ofs, BTreeNode<T, t> * node)
{
    if (node == nullptr)
        return;
    if (!node->m_leaf)
    {
        for (int i = 0; i < node->m_size + 1; i++)
        {
            ofs << "node" << ptr2str(node) << ":f" << i << ":s -> " << "node" << ptr2str(node->m_children[i]) << ":n;" << std::endl;
            draw_tree_edge(ofs, node->m_children[i]);
        }
    }
}

template <typename T, int t>
void Digraph::draw_tree_node(std::ofstream & ofs, BBTreeNode<T, t> * node)
{
    if (node == nullptr)
        return;
    ofs << "node" << ptr2str(node) << "[label=\"{{";
    for (int i = 0; i < node->m_size; i++)
    {
        if (i != 0)
            ofs << "|";
        ofs << node->m_keys[i];
    }
    ofs << "}|{";
    for (int i = 0; i <= node->m_size; i++)
    {
        if (i != 0)
            ofs << "|";
        ofs << "<f" << i << ">";
    }
    ofs << "}}\"];" << std::endl;

    if (!node->m_leaf)
    {
        for (int i = 0; i < node->m_size + 1; i++)
        {
            draw_tree_node(ofs, node->m_children[i]);
        }
    }
}

template <typename T, int t>
void Digraph::draw_tree_edge(std::ofstream & ofs, BBTreeNode<T, t> * node)
{
    if (node == nullptr)
        return;
    if (!node->m_leaf)
    {
        for (int i = 0; i < node->m_size + 1; i++)
        {
            ofs << "node" << ptr2str(node) << ":f" << i << ":s -> " << "node" << ptr2str(node->m_children[i]) << ":n;" << std::endl;
            draw_tree_edge(ofs, node->m_children[i]);
        }
    }
}

template <typename T, typename D, int t>
void Digraph::draw_tree_node(std::ofstream & ofs, BPTreeNode<T, D, t> * node)
{
    if (node == nullptr)
        return;
    ofs << "node" << ptr2str(node) << "[label=\"{{";
    for (int i = 0; i < node->m_size; i++)
    {
        if (i != 0)
            ofs << "|";
        ofs << node->m_keys[i];
    }
    ofs << "}|{";
    if (!node->m_leaf)
    {
        for (int i = 0; i <= node->m_size; i++)
        {
            if (i != 0)
                ofs << "|";
            ofs << "<f" << i << ">";
        }
    }
    else
    {
        for (int i = 0; i < node->m_size; i++)
        {
            if (i != 0)
                ofs << "|";
            ofs << "<f" << i << ">" << ((BPTreeLeafNode<T, D, t> *)node)->m_data[i];
        }
    }
    ofs << "}}\"];" << std::endl;
    if (!node->m_leaf)
    {
        for (int i = 0; i < node->m_size + 1; i++)
        {
            draw_tree_node(ofs, node->m_children[i]);
        }
    }
}

template <typename T, typename D, int t>
void Digraph::draw_tree_edge(std::ofstream & ofs, BPTreeNode<T, D, t> * node)
{
    if (node == nullptr)
        return;
    if (!node->m_leaf)
    {
        for (int i = 0; i < node->m_size + 1; i++)
        {
            ofs << "node" << ptr2str(node) << ":f" << i << ":s -> " << "node" << ptr2str(node->m_children[i]) << ":n;" << std::endl;
            draw_tree_edge(ofs, node->m_children[i]);
        }
    }
}

template <typename T, typename D, int t>
void Digraph::draw_leaf_link(std::ofstream & ofs, BPTreeNode<T, D, t> * node)
{
    if (node == nullptr)
        return;
    auto curr = (BPTreeLeafNode<T, D, t> *)node->leftmost();
    while (curr->m_next != nullptr)
    {
        ofs << "node" << ptr2str(curr) << ":e -> " << "node" << ptr2str(curr->m_next) << ":w;" << std::endl;
        curr = (BPTreeLeafNode<T, D, t> *)curr->m_next;
    }
    curr = (BPTreeLeafNode<T, D, t> *)node->rightmost();
    while (curr->m_prev != nullptr)
    {
        ofs << "node" << ptr2str(curr) << ":w -> " << "node" << ptr2str(curr->m_prev) << ":e;" << std::endl;
        curr = (BPTreeLeafNode<T, D, t> *)curr->m_prev;
    }
}

template <typename T>
void Digraph::draw_hash_bucket_node(std::ofstream & ofs, HashTableNode<T> * node)
{
    if (node == nullptr)
        return;
    while (node != nullptr)
    {
        ofs << "node" << ptr2str(node) <<"[label=\"" << node->m_key << "\"]" << ";" << std::endl;
        node = node->m_next;
    }
}

template <typename T>
void Digraph::draw_hash_bucket_link(std::ofstream & ofs, HashTableNode<T> * node, int slot)
{
    if (node == nullptr)
        return;
    ofs << "node0:f" << slot << ":e -> " << "node" << ptr2str(node) << ":w;" << std::endl;
    while (node->m_next != nullptr)
    {
        ofs << "node" << ptr2str(node) << ":e -> node" << ptr2str(node->m_next) << ":w;" << std::endl;
        node = node->m_next;
    }
}

template <typename T>
void Digraph::draw(Trie<T> & t)
{
    draw_before();

    std::ofstream ofs(m_dot_file);
    ofs << "digraph {" << std::endl;
    ofs << "rankdir=TB;" << std::endl;
    ofs << "node[shape=circle fillcolor=gray90 style=filled fontsize=24];" << std::endl;
    ofs << "subgraph cluster_tree {" << std::endl;
    ofs << "label=\"trie : size = " << t.size() << "\";" << std::endl;
    ofs << "pencolor=white;" << std::endl;

    auto root = t.m_root;
    draw_trie_edge(ofs, root);
    draw_trie_node(ofs, root);

    ofs << "}}" << std::endl;
    ofs.flush();
    ofs.close();

    draw_after();
}

template <typename T>
void Digraph::draw_trie_edge(std::ofstream & ofs, TrieNode<T> * node)
{
    static int count = 0;

    if (node == nullptr)
        return;
    if (node->m_children != nullptr)
    {
        for (int i = 0; i < node->m_size; i++)
        {
            if (i > 0)
            {
                ofs << "n" << count << "[style=invis];" << std::endl;
                ofs << "node" << ptr2str(node) << " -> n" << count << "[style=invis];" << std::endl;
                count++;
            }
            auto child = node->m_children[i];
            ofs << "node" << ptr2str(node) << " -> " << "node" << ptr2str(child) << ";" << std::endl;
            draw_trie_edge(ofs, child);
        }
    }
}

template <typename T>
void Digraph::draw_trie_node(std::ofstream & ofs, TrieNode<T> * node)
{
    if (node == nullptr)
        return;
    if (node->m_flag)
        ofs << "node" << ptr2str(node) << "[label=\"" << node->m_data << "\" fillcolor=navy style=filled fontcolor=white];" << std::endl;
    else
        ofs << "node" << ptr2str(node) << "[label=\"" << node->m_data << "\"];" << std::endl;
    if (node->m_children != nullptr)
    {
        for (int i = 0; i < node->m_size; i++)
        {
            auto child = node->m_children[i];
            draw_trie_node(ofs, child);
        }
    }
}