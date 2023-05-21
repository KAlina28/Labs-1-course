#include "HuffmanArchiver.h"
#include "HuffmanUnarchiver.h"

using namespace Huffman;

int main(int argc, char **argv) {
    try {
        if (argc < 6)
            throw std::invalid_argument("Wrong arguments!\n");
        int type = -1;
        std::string input, output;
        for (int i = 1; i < argc; i++) {
            std::string arg(argv[i]);
            if (arg == "-c") {
                type = 0;
            } else if (arg == "-u") {
                type = 1;
            } else if ((arg == "-f" || arg == "--file") && i < 5){
                input = argv[i + 1];
                i++;
            } else if ((arg == "-o" || arg == "--output") && i < 5) {
                output = argv[i + 1];
                i++;
            } else {
                throw std::invalid_argument("Wrong arguments!\n");
            }
        }
        if (type == -1 || input.empty() || output.empty() || input == output)
            throw std::invalid_argument("Wrong arguments!\n");

        if (!type) {
            HuffmanArchiver h;
            h.archieve(input, output);
        } else {
            HuffmanUnarchiver h;
            h.unarchive(input, output);
        }
    } catch (std::invalid_argument &e) {
        std::cout << e.what();
    }
    return 0;
}