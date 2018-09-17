/*
    Задача: 1386. Связанное множество
    
    Решение: DSU, алгоритм Краскала, минимальное остовное дерево, O(n^2 log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cmath>

struct Edge {
    int u, v; double cost;
    
    Edge(int u_ = 0, int v_ = 0, double c_ = 0.0) : u(u_), v(v_), cost(c_) { }
};

bool operator<(const Edge& a, const Edge& b) {
    if (a.cost < b.cost) return true;
    if (a.cost > b.cost) return false;
    return a.u < b.u || (a.u == b.u && a.v < b.v);
}

struct DSU {
    std::vector<int> parent, size;
    DSU(int n) : parent(1+n,0), size(1+n,1) {
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }
    int get_parent(int a) {
        return parent[a] == a ? a : parent[a] = get_parent(parent[a]);
    }
    void union_sets(int a, int b) {
        a = get_parent(a), b = get_parent(b);
        if (a != b) {
            if (size[a] < size[b]) std::swap(a,b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};

int main() {
    int n; scanf("%d", &n);
    std::vector<int> x(1+n), y(1+n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &x[i], &y[i]);
    }
    int m; scanf("%d", &m);
    std::vector<Edge> edges(m);
    for (auto& e : edges) {
        scanf("%d %d", &e.u, &e.v);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i+1; j <= n; ++j) {
            int dx = x[i] - x[j], dy = y[i] - y[j];
            edges.push_back(Edge(i,j,std::sqrt(dx*dx+dy*dy)));
        }
    }
    std::sort(edges.begin(), edges.end());
    DSU dsu(n); double answ = 0;
    for (auto& e : edges) {
        int pu = dsu.get_parent(e.u), pv = dsu.get_parent(e.v);
        if (pu != pv) {
            answ += e.cost;
            dsu.union_sets(e.u,e.v);
        }
    }
    printf("%0.5f", answ);
    return 0;
}