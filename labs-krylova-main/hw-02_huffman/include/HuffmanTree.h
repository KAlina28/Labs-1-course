#ifndef LABS_KRYLOVA_HUFFMANTREE_H
#define LABS_KRYLOVA_HUFFMANTREE_H

#include <string>
#include <algorithm>
#include <set>
#include <array>

namespace Huffman {
    const std::size_t NUM_OF_BYTES = 256;
    const std::size_t SIZE_OF_BYTE = 8;


    class Node {
    public:
        Node(Node *left, Node *right, std::size_t cnt);

        Node(Node *left, Node *right, std::size_t cnt, char symbol);

        ~Node();

        Node *get_left() const;

        Node *get_right() const;

        std::size_t get_cnt() const;

        char get_symbol() const;

        bool is_leaf() const;

    private:
        Node *_left;
        Node *_right;
        std::size_t _cnt;
        char _symbol;
    };

    struct NodeComparator {
        bool operator()(const Node *a, const Node *b) const;
    };

    class ArrayCnt {
    public:
        ArrayCnt();

        explicit ArrayCnt(const std::string &input);

        void build_array(const std::string &input);

        std::array<std::size_t, NUM_OF_BYTES> _array{};
    };


    class Tree {
    public:
        ~Tree();

        explicit Tree(const ArrayCnt &array);

        std::array<std::string, NUM_OF_BYTES> calc_codes() const;

        void merge_nodes() noexcept;

        void dfs(Node *node, std::array<std::string, NUM_OF_BYTES> &codes, const std::string& current_code) const;

    private:

        std::multiset<Node *, NodeComparator> _nodes;
        Node *_root = nullptr;

    };
}
#endif //LABS_KRYLOVA_HUFFMANTREE_H
