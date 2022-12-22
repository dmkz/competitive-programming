#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
void setmin(auto &x, const auto &y) {
    if (y < x) x = y;
}
void setmax(auto &x, const auto &y) {
    if (x < y) x = y;
}
using tiii = std::tuple<int,int,int>;
void part1() {
    std::string s;
    std::set<tiii> set;
    int edges{};
    while(std::getline(std::cin, s)) {
        int x,y,z;
        sscanf(s.c_str(), "%d,%d,%d", &x,&y,&z);
        set.insert({x,y,z});
    }
    for (auto [x,y,z] : set) {
        for (int dx = -1; dx <= 1; dx++)
            for (int dy = -1; dy <= 1; dy++)
                for (int dz = -1; dz <= 1; dz++) {
                    if (dx * dx + dy * dy + dz * dz != 1) {
                        continue;
                    }
                    int nx = x + dx, ny = y + dy, nz = z + dz;
                    edges += set.count({nx,ny,nz});
                }
    }
    std::cout << 6 * isz(set) - edges << std::endl;
}
const int INF = (int)1e9;

void part2() {
    std::string s;
    std::vector<tiii> pts;
    int xMin = +INF, yMin = +INF, zMin = +INF;
    int xMax = -INF, yMax = -INF, zMax = -INF;
    while(std::getline(std::cin, s)) {
        int x,y,z;
        sscanf(s.c_str(), "%d,%d,%d", &x,&y,&z);
        pts.emplace_back(x,y,z);
        setmin(xMin, x);
        setmin(yMin, y);
        setmin(zMin, z);
        setmax(xMax, x);
        setmax(yMax, y);
        setmax(zMax, z);
    }
    xMin--;
    yMin--;
    zMin--;
    xMax++;
    yMax++;
    zMax++;
    std::set<tiii> set, visited;
    for (auto &[x,y,z] : pts) {
        x -= xMin;
        y -= yMin;
        z -= zMin;
        set.insert({x,y,z});
    }
    xMax -= xMin;
    yMax -= yMin;
    zMax -= zMin;
    int sides{};
    std::function<void(int,int,int)> dfs = [&](int x, int y, int z) {
        if (set.count({x,y,z})) {
            sides++;
            return;
        }
        if(visited.count({x,y,z})) return;
        if (x < 0 || x > xMax) return;
        if (y < 0 || y > yMax) return;
        if (z < 0 || z > zMax) return;
        visited.insert({x,y,z});
        for (int dx = -1; dx <= 1; dx++)
            for (int dy = -1; dy <= 1; dy++)
                for (int dz = -1; dz <= 1; dz++) {
                    if (dx * dx + dy * dy + dz * dz != 1) {
                        continue;
                    }
                    int nx = x + dx, ny = y + dy, nz = z + dz;
                    dfs(nx,ny,nz);
                }
    };
    dfs(0,0,0);
    std::cout << sides << std::endl;
}

int main() {
    part2();
}