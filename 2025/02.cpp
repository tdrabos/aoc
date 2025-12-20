#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <vector>
#include <set>

bool isInvalid(const std::string& s) {
    const size_t n = s.size();
    // Try for every possible pattern length until n/2
    for (size_t len = 1; len <= n / 2; ++len) {
        // If n is not divisible by len then it cannot be the length of the pattern
        if (n % len != 0) continue;

        bool ok = true;
        for (size_t i = len; i < n; ++i) {
            // Pattern matching the first 'len' number for the rest of the input
            // If it fails, this len doesnt work, check len+1 if available
            if (s[i] != s[i % len]) { ok = false; break; }
        }
        if (ok) return true; // repeats >= 2 times
    }
    return false;
}

int main() {
    std::ifstream input("input.txt");

    if (!input) {
        std::cerr << "Failed to open input.txt\n";
        return 1;
    }

    std::set<std::uint64_t> invalid;
    std::uint64_t sum = 0;
    std::string line;
    std::getline(input, line);

    // Parse line until ','
    int dpos = line.find_first_of(',');
    bool done = false;
    while (!done) {
        std::string itv;

        if (dpos != -1)
            itv = line.substr(0, dpos);
        else {
            itv = line;
            done = true;
        }

        size_t dash = itv.find_first_of('-');
        if (dash == -1) continue;

        std::string loStr = itv.substr(0, dash);
        std::string hiStr = itv.substr(dash+1);
        
        std::uint64_t lo = std::stoull(loStr);
        std::uint64_t hi = std::stoull(hiStr);

        for (std::uint64_t i = lo; i<=hi; i++) {
            std::string numAsStr = std::to_string(i);
            if (isInvalid(numAsStr)) invalid.insert(i);
        }
        
        line = line.substr(dpos+1);
        dpos = line.find_first_of(',');
    }

    input.close();

    for (auto x : invalid) {
        sum += x;
    }

    std::cout << sum << std::endl;
    return 0;
}