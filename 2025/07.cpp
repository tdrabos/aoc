#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <map>

int main() {
    std::ifstream input("input.txt");
    std::map<std::int64_t, std::int64_t> beams = {};

    if (!input) {
        std::cerr << "Failed to open input.txt\n";
        return 1;
    }

    std::string line;
    int lineCt = 0;
    while (std::getline(input, line)) {
        if(line.empty()) continue;
        
        if (lineCt > 0) {
            std::map<std::int64_t, std::int64_t> updated = beams;

            auto it = beams.begin();
            while(it != beams.end()) {
                auto [idx, cnt] = *it;
                if (line[idx] == '^') {
                    if (updated.contains(idx-1)) updated[idx-1]+=updated[idx];
                    else updated[idx-1] = updated[idx]; 
                    if (updated.contains(idx+1)) updated[idx+1]+=updated[idx];
                    else updated[idx+1] = updated[idx];
                    
                    updated.erase(idx);
                }
                it++;
            }
            beams = updated;
        }
        else {
            beams[line.find('S')] = 1;
        }
        
        lineCt++;
        
    }
    input.close();

    std::int64_t n = 0;
    for (auto [idx, cnt] : beams) n+=cnt;

    std::cout << n << std::endl;

    return 0;
}