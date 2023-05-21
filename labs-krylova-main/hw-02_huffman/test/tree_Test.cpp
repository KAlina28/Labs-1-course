#include "doctest.h"
#include "HuffmanTree.h"

using namespace Huffman;

TEST_CASE("Node test") {
    auto* node1 = new Node(nullptr, nullptr, 256, 'a');
    SUBCASE("Leaf") {
        CHECK_EQ(node1->get_left(), nullptr);
        CHECK_EQ(node1->get_symbol(), 'a');
        CHECK(node1->is_leaf());
    }

    auto* node2 = new Node(nullptr, nullptr, 17, 'b');
    Node node = Node(node1, node2, 273);
    SUBCASE("Not leaf") {
        CHECK_EQ(node.get_left(), node1);
        CHECK_EQ(node.get_right(), node2);
        CHECK_EQ(node.get_cnt(), 273);
        CHECK(!node.is_leaf());
    }

    SUBCASE("Not leaf's leaf") {
        CHECK_EQ(node.get_left()->get_right(), nullptr);
        CHECK_EQ(node.get_right()->get_symbol(), 'b');
        CHECK_EQ(node.get_left()->get_cnt() + node.get_right()->get_cnt(), 273);
    }

    NodeComparator cmp;
    SUBCASE("NodeComparator") {
        CHECK(!cmp(node1, node2));
        CHECK(cmp(node1, &node));
    }
}

TEST_CASE("ArrayCnt test") {
    SUBCASE("Empty string") {
        auto arrayCnt = ArrayCnt("");
        for (auto a : arrayCnt._array)
            CHECK_EQ(a, 0);
    }

    SUBCASE("One letter string") {
        auto arrayCnt = ArrayCnt("aaaaaaaaaaaaa");
        for (std::size_t i = 0; i < arrayCnt ._array.size(); i++)
            if (i == 'a')
                CHECK_EQ(arrayCnt ._array[i], 13);
            else
                CHECK_EQ(arrayCnt ._array[i], 0);
    }

    SUBCASE("Random string 1") {
        auto arrayCnt  = ArrayCnt("abjAJaaAkJbbb...");
        CHECK_EQ(arrayCnt._array['a'], 3);
        CHECK_EQ(arrayCnt._array['b'], 4);
        CHECK_EQ(arrayCnt._array['j'], 1);
        CHECK_EQ(arrayCnt._array['A'], 2);
        CHECK_EQ(arrayCnt._array['J'], 2);
        CHECK_EQ(arrayCnt._array['k'], 1);
        CHECK_EQ(arrayCnt._array['.'], 3);
    }

    SUBCASE("Random string 2") {
        auto arrayCnt = ArrayCnt("she looks perfect");
        CHECK_EQ(arrayCnt._array['s'], 2);
        CHECK_EQ(arrayCnt._array['h'], 1);
        CHECK_EQ(arrayCnt._array['e'], 3);
        CHECK_EQ(arrayCnt._array['l'], 1);
        CHECK_EQ(arrayCnt._array['o'], 2);
        CHECK_EQ(arrayCnt._array['k'], 1);
        CHECK_EQ(arrayCnt._array['p'], 1);
        CHECK_EQ(arrayCnt._array['r'], 1);
        CHECK_EQ(arrayCnt._array['f'], 1);
        CHECK_EQ(arrayCnt._array['c'], 1);
        CHECK_EQ(arrayCnt._array['t'], 1);
    }

    SUBCASE("Random string 3") {
        auto arrayCnt = ArrayCnt("AMmama");
        CHECK_EQ(arrayCnt._array['A'], 1);
        CHECK_EQ(arrayCnt._array['M'], 1);
        CHECK_EQ(arrayCnt._array['m'], 2);
        CHECK_EQ(arrayCnt._array['a'], 2);
    }
}

TEST_CASE("Tree test") {
    std::array<std::string, NUM_OF_BYTES> codes;
    SUBCASE("Empty string") {
        auto tree = Tree(ArrayCnt(""));
        codes = tree.calc_codes();
        for (auto e : codes)
            CHECK_EQ(e, "");
    }

    SUBCASE("One letter string") {
        auto ht = Tree(ArrayCnt("aaaaaaaaaaaaa"));
        codes = ht.calc_codes();
        for (std::size_t i = 0; i < codes.size(); i++)
            if (i == 'a')
                CHECK_EQ(codes[i], "0");
            else
                CHECK_EQ(codes[i], "");
    }

    SUBCASE("Random string 1") {
        auto ht = Tree(ArrayCnt("abbabababcccccdddddd"));
        codes = ht.calc_codes();
        CHECK_EQ(codes['a'], "00");
        CHECK_EQ(codes['b'], "01");
        CHECK_EQ(codes['c'], "10");
        CHECK_EQ(codes['d'], "11");
    }

    SUBCASE("Random string 2") {
        auto ht = Tree(ArrayCnt("aaaaaaabbbbbccccdddeef"));
        codes = ht.calc_codes();
        CHECK_EQ(codes['a'], "11");
        CHECK_EQ(codes['b'], "01");
        CHECK_EQ(codes['c'], "00");
        CHECK_EQ(codes['d'], "100");
        CHECK_EQ(codes['e'], "1011");
        CHECK_EQ(codes['f'], "1010");
    }

    SUBCASE("Random string 3") {
        auto ht = Tree(ArrayCnt("AAAAABBBBB"));
        codes = ht.calc_codes();
        CHECK_EQ(codes['A'], "0");
        CHECK_EQ(codes['B'], "1");
    }

    SUBCASE("Random string 4") {
        auto ht = Tree(ArrayCnt("AAAAABBBBBCCCCC"));
        codes = ht.calc_codes();
        CHECK_EQ(codes['A'], "10");
        CHECK_EQ(codes['B'], "11");
        CHECK_EQ(codes['C'], "0");
    }

    SUBCASE("Random string 5") {
        auto ht = Tree(ArrayCnt("Hello"));
        codes = ht.calc_codes();
        CHECK_EQ(codes['H'], "00");
        CHECK_EQ(codes['e'], "01");
        CHECK_EQ(codes['l'], "11");
        CHECK_EQ(codes['o'], "10");
    }
}