#include <fstream>
#include "util.h"

const std::size_t SIZE_OF_BYTE = 8;


unsigned char converter(std::string str){
    unsigned char c = '\0';
    while(str.size() < SIZE_OF_BYTE)
        str.push_back('0');
    for (std::size_t i = 0; i < SIZE_OF_BYTE; i++)
        c += (str[i] - '0') * (1 << (SIZE_OF_BYTE - i - 1));
    return c;
}

bool compare(const std::string& first_file, const std::string& second_file) {
    std::ifstream file1(first_file, std::ifstream::ate | std::ifstream::binary);
    std::ifstream file2(second_file, std::ifstream::ate | std::ifstream::binary);
    const std::ifstream::pos_type fileSize = file1.tellg();

    if (fileSize != file2.tellg()) {
        return false;
    }

    file1.seekg(0);
    file2.seekg(0);

    std::istreambuf_iterator<char> begin1(file1);
    std::istreambuf_iterator<char> begin2(file2);

    return std::equal(begin1, std::istreambuf_iterator<char>(), begin2);
}



