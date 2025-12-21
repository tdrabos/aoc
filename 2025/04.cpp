#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <vector>
#include <tuple>

bool canReach(const std::vector<std::string>& map, uint row, uint col) {
    // Neighbors map
    const std::vector<std::tuple<int,int>> dirs{
        {row-1, col-1}, {row-1, col}, {row-1, col+1},
        {row, col-1},   /* Elem */    {row, col+1},
        {row+1, col-1}, {row+1, col}, {row+1, col+1}
    };

    int counter = 0, it = 0;
    while (counter < 4 && it < dirs.size()) {
        auto [r, c] = dirs[it];
        it++;
        if (r < 0 || c < 0) continue;
        if (map[r][c] == '@') counter++;
    }

    return counter < 4;
}

int main() {
    std::ifstream input("input.txt");

    if (!input) {
        std::cerr << "Failed to open input.txt\n";
        return 1;
    }

    std::vector<std::string> grid;
    std::string line;
    uint n = 0;
    while (std::getline(input, line)) {
        if(line.empty()) continue;
        grid.push_back(line);
    }
    input.close();

    bool done = false;
    while (!done) {
        int removedPerIt = 0;
        for (int i = 0; i<grid.size(); i++) {
            for (int j = 0; j<grid[i].size(); j++) {
                if (grid[i][j] == '@' && canReach(grid, i, j)) {
                    grid[i][j] = '.';
                    removedPerIt++;
                }
            }
        }
        if (removedPerIt == 0) done = true;
        else n += removedPerIt;
    }

    std::cout << n << std::endl;

    return 0;
}