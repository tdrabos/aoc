#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cmath>
#include <vector>
#include <tuple>
#include <set>
#include <numeric>
#include <algorithm>

struct Point3D {
    std::int64_t x, y, z;

    auto operator<=>(const Point3D&) const = default;
};

inline std::ostream& operator<<(std::ostream& os, const Point3D& p) {
    return os << '(' << p.x << ", " << p.y << ", " << p.z << ')';
}

// Union Find with Disjoint Set Union
class UnionFind {
    std::vector<int> parent, size;
    int componentCount;
public:
    UnionFind(int n) : parent(n), size(n, 1), componentCount(n) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); // compress path so next time access is faster
    }

    void unite(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) return;

        if (size[ra] < size[rb]) std::swap(ra, rb); // always merge under the bigger tree
        parent[rb] = ra;
        size[ra] += size[rb];
        componentCount--;
    }

    std::vector<int> getSize() {
        return size;
    }

    int getComponentCount() {return componentCount;}
    
};

long double distance(Point3D p1, Point3D p2) {
    std::int64_t dx = p2.x - p1.x;
    std::int64_t dy = p2.y - p1.y;
    std::int64_t dz = p2.z - p1.z;

    return std::hypot(std::hypot(dx, dy), dz);
}

int main() {
    std::ifstream input("input.txt");
    std::vector<Point3D> points;

    if (!input) {
        std::cerr << "Failed to open input.txt\n";
        return 1;
    }

    std::string line;
    while (std::getline(input, line)) {
        if(line.empty()) continue;

        Point3D p;
        std::vector<std::string> nums;
        std::istringstream iss(line);
        std::string token;
        while (std::getline(iss, token, ',')) {
            nums.push_back(token);
        }

        p.x = std::stoi(nums[0]);
        p.y = std::stoi(nums[1]);
        p.z = std::stoi(nums[2]);

        points.push_back(p);
    }
    input.close();

    std::vector<std::tuple<int, int, long double>> pairs = {};
    std::set<std::pair<int, int>> seen = {};

    // Get all the distances
    for (int i = 0; i < points.size(); i++) {
        for (int j = 0; j < points.size(); j++) {
            if (i == j) continue;
            auto dst = distance(points[i], points[j]);
            if (!seen.contains({j, i})) {
                pairs.emplace_back(i, j, dst);
                seen.insert({i, j});
            }
        }
    }

    // Sort them ascending
    std::sort(pairs.begin(), pairs.end(),
        [](auto const& a, auto const& b) {
          return std::get<2>(a) < std::get<2>(b);
        });

    UnionFind uf = UnionFind(points.size());
    
    int it = 0;
    int targetI, targetJ;
    while (uf.getComponentCount() != 1 && it < pairs.size()) {
        auto [i, j, _] = pairs[it];
        uf.unite(i, j);
        targetI = i;
        targetJ = j;
        it++;
    }

    Point3D i = points[targetI],
            j = points[targetJ];
    std::cout << i << std::endl;
    std::cout << j << std::endl;
    std::cout << i.x * j.x << std::endl;

    return 0;
}