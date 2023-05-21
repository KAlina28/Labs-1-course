#include "HuffmanTree.h"

using namespace Huffman;

//node
Node::Node(Node *left, Node *right, size_t cnt) :
        _left(left), _right(right), _cnt(cnt) {}

Node::Node(Node *left, Node *right, size_t cnt, char symbol) :
        Node(left, right, cnt) {
    _symbol = symbol;
}

Node::~Node() {
    delete _left;
    delete _right;
}

size_t Node::get_cnt() const {
    return _cnt;
}

Node *Node::get_left() const {
    return _left;
}

Node *Node::get_right() const {
    return _right;
}

char Node::get_symbol() const {
    return _symbol;
}

bool Node::is_leaf() const {
    return (_left == nullptr && _right == nullptr);
}

//nodecomporator
bool NodeComparator::operator()(const Node *a, const Node *b) const {
    return a->get_cnt() < b->get_cnt();
}

//arraycnt
ArrayCnt::ArrayCnt() {};

ArrayCnt::ArrayCnt(const std::string &input) {
    build_array(input);
}

void ArrayCnt::build_array(const std::string &input) {
    for (auto el: input) {
        _array[(unsigned char)el]++;
    }
}

//tree
Tree::~Tree() {
    delete _root;
}

Tree::Tree(const ArrayCnt &array) {
    for (std::size_t i = 0; i < array._array.size(); ++i) {
        if (array._array[i] > 0)
            _nodes.insert(new Node(nullptr, nullptr, array._array[i], (char) i));
    }
    while (_nodes.size() > 1) {
        merge_nodes();
    }
    if (_nodes.size() == 1) {
        _root = *_nodes.begin();
    }
}

std::array<std::string, NUM_OF_BYTES> Tree::calc_codes() const {
    std::array<std::string, NUM_OF_BYTES> codes;
    if (_root != nullptr) {
        std::string start_code;
        if (_root->is_leaf())
            start_code = "0";
        dfs(_root, codes, start_code);
    }
    return codes;
}

void Tree::merge_nodes() noexcept {
    Node *min1 = *_nodes.begin();
    _nodes.erase(_nodes.begin());
    Node *min2 = *_nodes.begin();
    _nodes.erase(_nodes.begin());
    _nodes.insert(new Node(min1, min2, min1->get_cnt() + min2->get_cnt()));

}

void Tree::dfs(Node *node, std::array<std::string, NUM_OF_BYTES> &codes, const std::string& current_code) const {
    if (node->is_leaf()) {
        codes[(unsigned char) node->get_symbol()] = current_code;
    } else {
        if (node->get_left() != nullptr) {
            dfs(node->get_left(), codes, current_code + "0");
        }
        if (node->get_right() != nullptr) {
            dfs(node->get_right(), codes, current_code + "1");
        }
    }
}

