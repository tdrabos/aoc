#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

const std::uint16_t DIGITS = 12;

// Calculates the largest number witt length n 
std::string largestN(const std::string& seq, std::uint16_t n) {
    if (n == 0 || seq.size() < n) return "";

    char max; 
    int maxNum = -1, maxIdx;
    for (int i = 0; i<seq.size()-n+1; i++) {
        int num = seq[i] - '0';
        if (num > maxNum) {
            max = seq[i];
            maxNum = num;
            maxIdx = i;
        }
    }
    std::string tail = largestN(seq.substr(maxIdx+1), n-1);
    return max + tail;
}

int main() {
    std::ifstream input("input.txt");

    if (!input) {
        std::cerr << "Failed to open input.txt\n";
        return 1;
    }

    std::int64_t sum = 0;

    std::string line;
    while (std::getline(input, line)) {
        if(line.empty()) continue;

        std::string numStr = largestN(line, DIGITS);
        sum += std::stoll(numStr);
        
    }
    input.close();

    std::cout << sum << std::endl;

    return 0;
}