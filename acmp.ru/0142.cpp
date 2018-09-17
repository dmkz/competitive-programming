/*
    Задача: 142. Минимальный каркас
    
    Решение: DSU, графы, деревья, алгоритм Краскала, O(n log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>

struct DSU {

    std::vector<int> parent, size;
    
    DSU(int n) {
        parent.resize(1+n);
        size.resize(1+n);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i; size[i] = 1;
        }
    }
    
    int get_parent(int u) {
        return parent[u] == u ? u : parent[u] = get_parent(parent[u]);
    }
    
    void union_sets(int a, int b) {
        a = get_parent(a);
        b = get_parent(b);
        if (a != b) {
            if (size[a] < size[b]) std::swap(a,b);
            parent[b] = a;
            size[a] += size[b];
        }
    }

};


struct Edge {
    int u, v, cost;
};

bool operator<(const Edge& a, const Edge& b) {
    if (a.cost < b.cost) return true;
    if (a.cost > b.cost) return false;
    return a.u < b.u || (a.u == b.u && a.v < b.v);
}

int main() {
    int n, m, answ = 0; scanf("%d %d", &n, &m);
    std::vector<Edge> edges(m);
    for (auto& e : edges) {
        scanf("%d %d %d", &e.u, &e.v, &e.cost);
    }
    std::sort(edges.begin(), edges.end());
    DSU dsu(n);
    for (auto& e : edges) {
        int pu = dsu.get_parent(e.u);
        int pv = dsu.get_parent(e.v);
        if (pu != pv) {
            answ += e.cost;
            dsu.union_sets(e.u, e.v);
        }
    }
    printf("%d", answ);
    return 0;
}