#include "HuffmanArchiver.h"
#include "util.h"



using namespace Huffman;

void HuffmanArchiver::archieve(const std::string &input, const std::string &output) {
    try {
        read(input);
    } catch (const std::ifstream::failure &e) {
        std::cout << "Can't read file" << std::endl;
        return;
    }
    _arrayCnt.build_array(_input);

    auto t = new Tree(_arrayCnt);
    _codes = t->calc_codes();
    delete t;

    try {
        write(output);
    } catch (const std::ifstream::failure &e) {
        std::cout << "Can't write to file" << std::endl;
        return;
    }
}

void HuffmanArchiver::read(const std::string &input) {
    std::ifstream in(input);
    in.exceptions(std::ifstream::failbit);

    in.seekg(0, std::ios::end);
    _input.reserve(in.tellg());
    in.seekg(0, std::ios::beg);
    _input.assign(std::istreambuf_iterator<char>(in),std::istreambuf_iterator<char>());
}


void HuffmanArchiver::write(const std::string &output) const {
    std::ofstream out(output);
    out.exceptions(std::ofstream::failbit);
    for (auto e: _arrayCnt._array) {
        out.write(reinterpret_cast<const char *>(&e), sizeof(e));
    }

    Encode encoder(_codes);
    std::string encoded = encoder.encode(_input);
    std::size_t extra_bits = (SIZE_OF_BYTE - encoded.length() % SIZE_OF_BYTE) % SIZE_OF_BYTE;
    out.write(reinterpret_cast<const char *>(&extra_bits), sizeof(extra_bits));
    std::cout << _input.size() << std::endl;
    std::cout << (encoded.size() + extra_bits) / SIZE_OF_BYTE << std::endl;
    std::cout << _arrayCnt._array.size() * sizeof(_arrayCnt._array[0]) + sizeof(extra_bits) << std::endl;

    for (std::size_t i = 0; i < encoded.size(); i += SIZE_OF_BYTE) {
        unsigned char outp = converter(encoded.substr(i, std::min(encoded.size() - i, SIZE_OF_BYTE)));
        out.write(reinterpret_cast<const char *>(&outp), sizeof(outp));
    }

}

std::string Encode::encode(const std::string &str) const {
    std::string code;
    for (auto i: str) {
        code += _codes[(unsigned char)i];
    }
    return code;
}

Encode::Encode(std::array<std::string, NUM_OF_BYTES> codes) : _codes(std::move(codes)) {};

