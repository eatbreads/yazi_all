#pragma once

#include <cstdio>
#include <sstream>
#include <fstream>
#include <string>
using std::string;

#include <utility/time.h>
using namespace yazi::utility;

#include <fs/file.h>
#include <fs/directory.h>
using namespace yazi::fs;

#include <string>
#include <ttl/array.h>
#include <ttl/vector.h>
#include <ttl/list.h>
#include <ttl/forward_list.h>
#include <ttl/stack.h>
#include <ttl/queue.h>
#include <ttl/heap.h>
#include <ttl/deque.h>
#include <ttl/skip_list.h>
#include <ttl/bs_tree.h>
#include <ttl/avl_tree.h>
#include <ttl/rb_tree.h>
#include <ttl/b_tree.h>
#include <ttl/bb_tree.h>
#include <ttl/bp_tree.h>
#include <ttl/hash_table.h>
#include <ttl/hash_map.h>
#include <ttl/trie.h>

namespace ttl
{
    class Digraph
    {
    public:
        Digraph();
        ~Digraph() = default;

        void delay(int milliseconds);

        template <typename T, int N>
        void draw(Array<T, N> & a);

        template <typename T>
        void draw(Vector<T> & v);

        template <typename T>
        void draw(List<T> & l);

        template <typename T>
        void draw(ForwardList<T> & l);

        template <typename T, typename Container>
        void draw(Stack<T, Container> & s);

        template <typename T, typename Container>
        void draw(Queue<T, Container> & q);

        template <typename T>
        void draw(Heap<T> & h);

        template <typename T, int N>
        void draw(Deque<T, N> & d);

        template <typename T, int max_level>
        void draw(SkipList<T, max_level> & s);

        template <typename T>
        void draw(BSTree<T> & t);

        template <typename T>
        void draw(AVLTree<T> & t);

        template <typename T>
        void draw(RBTree<T> & t);

        template <typename T, int t>
        void draw(BTree<T, t> & tree);

        template <typename T, int t>
        void draw(BBTree<T, t> & tree);

        template <typename T, typename D, int t>
        void draw(BPTree<T, D, t> & tree);

        template <typename T, typename Hash>
        void draw(HashTable<T, Hash> & table);

        template <typename T, typename Hash, typename Container>
        void draw(HashMap<T, Hash, Container> & table);

        template <typename T>
        void draw(Trie<T> & t);

    private:
        void draw_before();
        void draw_after();
        void sleep();   // 控制图片展示间隔时间
        string ptr2str(void * ptr);

        template <typename T>
        void draw_tree_node(std::ofstream & ofs, BSTreeNode<T> * node);

        template <typename T>
        void draw_tree_edge(std::ofstream & ofs, BSTreeNode<T> * node);

        template <typename T>
        void draw_tree_node(std::ofstream & ofs, AVLTreeNode<T> * node);

        template <typename T>
        void draw_tree_edge(std::ofstream & ofs, AVLTreeNode<T> * node);

        template <typename T>
        void draw_tree_node(std::ofstream & ofs, RBTreeNode<T> * node);

        template <typename T>
        void draw_tree_edge(std::ofstream & ofs, RBTreeNode<T> * node);

        template <typename T, int t>
        void draw_tree_node(std::ofstream & ofs, BTreeNode<T, t> * node);

        template <typename T, int t>
        void draw_tree_edge(std::ofstream & ofs, BTreeNode<T, t> * node);

        template <typename T, int t>
        void draw_tree_node(std::ofstream & ofs, BBTreeNode<T, t> * node);

        template <typename T, int t>
        void draw_tree_edge(std::ofstream & ofs, BBTreeNode<T, t> * node);

        template <typename T, typename D, int t>
        void draw_tree_node(std::ofstream & ofs, BPTreeNode<T, D, t> * node);

        template <typename T, typename D, int t>
        void draw_tree_edge(std::ofstream & ofs, BPTreeNode<T, D, t> * node);

        template <typename T, typename D, int t>
        void draw_leaf_link(std::ofstream & ofs, BPTreeNode<T, D, t> * node);

        template <typename T>
        void draw_hash_bucket_node(std::ofstream & ofs, HashTableNode<T> * node);

        template <typename T>
        void draw_hash_bucket_link(std::ofstream & ofs, HashTableNode<T> * node, int slot);

        template <typename T>
        void draw_trie_edge(std::ofstream & ofs, TrieNode<T> * node);

        template <typename T>
        void draw_trie_node(std::ofstream & ofs, TrieNode<T> * node);

    private:
        static int s_count;     // 生成图片默认序号从 0 开始
        int m_delay = 500;      // 默认每张图片延迟 500 毫秒展示
        string m_dot_file;      // dot 文件名称
        string m_png_file;      // png 文件名称
    };

#include <ttl/digraph.inl>

}