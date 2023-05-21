#ifndef HW_02_HUFFMAN_HUFFMANUNARCHIVER_H
#define HW_02_HUFFMAN_HUFFMANUNARCHIVER_H

#include "HuffmanTree.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <exception>

namespace Huffman {

    class HuffmanUnarchiver {
    public:
        void unarchive(const std::string& input, const std::string& output);
        void read(const std::string& input);
        void write(const std::string& output) const;
    private:
        ArrayCnt _arrayCnt;
        std::size_t _extra_bits;
        std::string _output;
        std::array<std::string, NUM_OF_BYTES> _codes;
    };
}

#endif //HW_02_HUFFMAN_HUFFMANUNARCHIVER_H
