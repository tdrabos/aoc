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

    int dial = 50;
    std::int64_t zeros = 0;

    std::string line;
    while (std::getline(input, line)) {
        if(line.empty()) continue;

        int num = std::stoi(line.substr(1));

        if (num >= 100) {
            zeros += num / 100;
            num = num % 100;
        }
        if (line[0] == 'L') num *= -1;
        
        int next = dial + num;

        if (next >= 100) {
            ++zeros;
            next -= 100;
        }
        else if (next < 0) {
            next += 100;
            if (dial != 0) ++zeros;
        }
        else if (next == 0) ++zeros;

        dial = next;
        
    }
    input.close();

    std::cout << zeros << std::endl;

    return 0;
}