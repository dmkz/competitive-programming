/*
    Problem: 107A. Dorm Water Supply
    
    Solution: graphs, sorting, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
    int vert, cost;
};

const Edge UNDEF = Edge{-1,-1};

inline bool operator==(const Edge& a,const Edge& b) {
    return a.vert == b.vert && a.cost == b.cost;
}

inline bool operator!=(const Edge& a,const Edge& b) {
    return !(a == b);
}

struct Triple {
    int a, b, cost;
};

inline bool operator<(const Triple& a, const Triple& b) {
    return a.a < b.a || (a.a == b.a && (a.b < b.b || (a.b == b.b && a.cost < b.cost)));
}

int main() {
    int n, p; std::cin >> n >> p;
    std::vector<Edge> to(n, UNDEF), from(n, UNDEF);
    for (int i = 0; i < p; ++i) {
        int a, b, d; std::cin >> a >> b >> d;
        --a,--b;
        to[a] = Edge{b,d};
        from[b] = Edge{a,d};
    }
    std::vector<bool> visited(n);
    std::vector<Triple> answ;
    for (int v = 0; v < n; ++v) {
        if (!visited[v] && from[v] == UNDEF && to[v] != UNDEF) {
            visited[v] = true;
            int min = to[v].cost;
            int u = to[v].vert;
            while (to[u] != UNDEF) {
                visited[u] = true;
                min = std::min(to[u].cost, min);
                u = to[u].vert;
            }
            visited[u] = true;
            answ.push_back(Triple{v, u, min});
        }
    }
    std::sort(answ.begin(), answ.end());
    std::cout << answ.size() << '\n';
    for (auto t : answ) {
        std::cout << t.a+1 << ' ' << t.b+1 << ' ' << t.cost << '\n';
    }
    return 0;
}