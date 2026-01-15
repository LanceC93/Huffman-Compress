#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <unordered_map>

std::vector<uint8_t> read_all_bytes(std::istream& in) {
    return {
        std::istreambuf_iterator<char>(in),
        std::istreambuf_iterator<char>()
    };
}

std::unordered_map<uint8_t, uint32_t> create_frequency_table(const std::vector<uint8_t>& data) {
    std::unordered_map<uint8_t, uint32_t> freq_table;
    for (uint8_t byte : data) {
        freq_table[byte]++;
    }
    return freq_table;
}

int main(int argc, char const *argv[]) {
    //check for correct number of arguments
    if (argc < 3 || argc > 4) {
        std::cout << "Usage: " << argv[0] << " <compress|decompress> <source> [dest]" << std::endl;
        return 1;
    }

    //check if first argument is valid
    std::string mode = argv[1];
    if (mode != "compress" && mode != "decompress") {
        std::cout << "First argument must be 'compress' or 'decompress'" << std::endl;
        return 1;
    }
    
    //read source file
    std::ifstream source(argv[2], std::ios::binary);
    if(!source) {
        std::cout << "Error: Could not open source file: " << argv[2] << std::endl;
        return 1;
    }
    std::vector<uint8_t> input = read_all_bytes(source);
    source.close();

    if(mode == "compress") {
        //only want this message to show if dest is given so i can pipe output otherwise
        if(argc == 4) {
            std::cout << "Compressing: " << argv[2] << std::endl;
        }
        auto freq_table = create_frequency_table(input);
    } else {
        //only want this message to show if dest is given so i can pipe output otherwise
        if(argc == 4) {
            std::cout << "Decompressing: " << argv[2] << std::endl;
        }
    }

    return 0;
}