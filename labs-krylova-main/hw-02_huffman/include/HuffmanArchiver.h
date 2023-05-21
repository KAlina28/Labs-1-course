#ifndef HW_02_HUFFMAN_HUFFMANARCHIVER_H
#define HW_02_HUFFMAN_HUFFMANARCHIVER_H

#include "HuffmanTree.h"
#include <fstream>
#include <iostream>

namespace Huffman{
    class HuffmanArchiver{
    public:
        void read(const std::string& input);
        void write(const std::string& output) const;
        void archieve(const std::string  &input, const std::string &output);

    private:
        std::string _input;
        ArrayCnt _arrayCnt;
        std::array<std::string , NUM_OF_BYTES> _codes;

    };

    class Encode{
    public:
        Encode(std::array<std::string, NUM_OF_BYTES> codes);
        std::string encode(const std::string &str) const;
    private:
        std::array<std::string, NUM_OF_BYTES> _codes;
    };

}
#endif //HW_02_HUFFMAN_HUFFMANARCHIVER_H
