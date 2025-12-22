#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <vector>
#include <tuple>

int main() {
    std::ifstream input("input.txt");

    if (!input) {
        std::cerr << "Failed to open input.txt\n";
        return 1;
    }

    std::vector<std::tuple<std::uint64_t, std::uint64_t>> ranges = {};
    size_t n = 0;

    std::string line;
    int mode = 0;
    while (std::getline(input, line)) {
        if(line.empty()) {
            mode = 1;
            continue;
        }

        // Insert sorted (needed for part2)
        if (mode == 0) {
            uint dash = line.find('-');
            std::string loStr = line.substr(0, dash);
            std::string hiStr = line.substr(dash+1);
            auto elem = std::tuple<std::int64_t, std::int64_t>{std::stoll(loStr), std::stoll(hiStr)};

            auto pos = upper_bound(ranges.begin(), ranges.end(), elem);
            ranges.insert(pos, elem);
        }

        if (mode == 1) {
            std::int64_t id = std::stoll(line);

            bool ok = false;
            for (auto [lo, hi] : ranges) {
                if (lo <= id && id <= hi) {ok=true; break;}
            }

            if(ok) n++;
        }
    }
    input.close();

    // part2
    auto [lo0, hi0] = ranges[0];
    std::uint64_t allIdxs = 0,
                currentHi = hi0,
                currentLo = lo0;

    for (size_t i = 1; i<ranges.size(); i++) {
        auto [lo, hi] = ranges[i];
        // If there is overlap, merge
        if (lo <= currentHi) {
            if (hi > currentHi) currentHi = hi;
        }
        // Else, register the current ids and reset the current high and low bound
        else {
            allIdxs += currentHi - currentLo + 1;
            currentHi = hi;
            currentLo = lo;
        }
    }

    // since the last interval is not yet registered, do it after the loop finished
    allIdxs += currentHi-currentLo+1;

    std::cout << n << std::endl;
    std::cout << allIdxs << std::endl;

    return 0;
}