/*
    Problem: 217A. Ice Skating
    Solution: graphs, dfs, geometry
*/
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

struct Point {
    int row, col, id;
};

inline bool operator<(const Point& a, const Point& b) {
    return a.row < b.row || (a.row == b.row && a.col < b.col);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<std::vector<Point>> ptr(1+1000), ptc(1+1000);
    for (int i = 0; i < n; ++i) {
        int r, c; std::cin >> r >> c;
        ptr[r].push_back(Point{r,c,i});
        ptc[c].push_back(Point{r,c,i});
        
    }
    // Надо соединить ребрами соседние вершины!
    std::vector<std::vector<int>> edges(n);
    for (int r = 1; r <= 1000; ++r) {
        auto& vec = ptr[r];
        std::sort(vec.begin(), vec.end());
        for (int i = 1; i < (int)vec.size(); ++i) {
            int a = vec[i-1].id;
            int b = vec[i-0].id;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
    }
    for (int c = 1; c <= 1000; ++c) {
        auto& vec = ptc[c];
        std::sort(vec.begin(), vec.end());
        for (int i = 1; i < (int)vec.size(); ++i) {
            int a = vec[i-1].id;
            int b = vec[i-0].id;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }
    }
    
    // И запустить поиск компонент связности:
    std::vector<int> part(n,0);
    int nParts = 0;
    std::function<void(int)> visit = [&](int curr) {
        for (auto& next : edges[curr]) {
            if (!part[next]) {
                part[next] = part[curr];
                visit(next);
            }
        }
    };
    for (int i = 0; i < n; ++i) {
        if (!part[i]) {
            part[i] = ++nParts;
            visit(i);
        }
    }
    std::cout << nParts-1;
    return 0;
}