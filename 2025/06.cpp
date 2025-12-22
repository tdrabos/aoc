#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <vector>
#include <set>
#include <numeric>

int NUM_ROWS = 4;

int main() {
    std::ifstream input("input.txt");
    std::vector<std::vector<char>> sheet;
    std::set<char> ops = {'+', '*'};

    if (!input) {
        std::cerr << "Failed to open input.txt\n";
        return 1;
    }

    std::string line;
    int rowCount = 1;
    while (std::getline(input, line)) {
        if(line.empty()) continue;
        
        std::vector<char> tokens;
        for (char c : line ) {
            tokens.push_back(c);
        }

        sheet.push_back(tokens);   
    }
    input.close();

    std::int64_t sum = 0;
    std::vector<std::int64_t> currentNums = {};

    // transpose, form numbers from the rows and do the op
    for (int col = 0; col < sheet[0].size(); col++) {
        std::string currentNumStr = "";
        char currentOp;
        for (int row = 0; row<sheet.size(); row++) {
            currentNumStr += sheet[row][col];
        }
        size_t sz = currentNumStr.size();
        bool numLine = currentNumStr.find_first_not_of(' ') != std::string::npos;

        if(numLine) {
            if (ops.contains(currentNumStr[sz-1])) {
                currentOp = currentNumStr[sz-1];
                currentNumStr = currentNumStr.substr(0, sz-1);
            }

            currentNums.push_back(std::stoll(currentNumStr));
        }
        
        // if the line is full space (or we reached the last line), then we execute the op on the current numbers
        if (!numLine || col == sheet[0].size()-1) {
            switch(currentOp) {
                case '*': {
                    std::cout << "*: ";
                    for (auto n : currentNums) {
                        std::cout << n << ", ";
                    }
                    std::cout << std::endl;
                    sum += std::accumulate(currentNums.begin(), currentNums.end(), 1LL, std::multiplies<std::int64_t>());
                    break;
                }
                case '+': {
                    std::cout << "+: ";
                    for (auto n : currentNums) {
                        std::cout << n << ", ";
                    }
                    std::cout << std::endl;
                    sum += std::reduce(currentNums.begin(), currentNums.end());
                    break;
                }
                default: std::cerr << "Unsupported operation\n";
            }
            currentNums = {};
        }
    }

    std::cout << sum << std::endl;

    return 0;
}