#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

int main() {
    std::ifstream input("input.txt");

    if (!input) {
        std::cerr << "Failed to open input.txt\n";
        return 1;
    }

    std::string line;
    while (std::getline(input, line)) {
        if(line.empty()) continue;
        
    }
    input.close();

    return 0;
}