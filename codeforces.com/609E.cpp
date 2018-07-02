/*
    Solution: Sparse Table on tree, DSU, MST, O(n log(n))
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <functional>

struct DSU {
    // Disjoin Set Union: size[item] = size of set(item), parent[item] = parent of set(item)
    std::vector<int> size, parent;
    // Construct DSU fixed size:
    DSU(const int nItems) : size(nItems, 0), parent(nItems, -1) { 
        for (int v = 0; v < (int)size.size(); ++v) {
            parent[v] = v;
            size[v] = 1;
        }
    }
    // Find parent of set(v):
    int find_set(const int v) {
        return v == parent[v] ? v : parent[v] = find_set(parent[v]);
    }
    // Find size of set(v):
    int get_size(const int v) {
        return size.at(find_set(v));
    }
    // Union set(a) and set(b):
    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size[a] < size[b]) {
                std::swap(a, b);
            }
            parent[b] = a;
            size[a] += size[b];
        }
    }
};

typedef long long ll;

struct Edge { // struct for edge
    int u, v, cost, id;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nVert, nEdges;
    std::cin >> nVert >> nEdges;
    
    std::vector<Edge> edges;
    for (int i = 0; i < nEdges; ++i) {
        int u, v, cost;
        std::cin >> u >> v >> cost;
        edges.push_back(Edge{u-1,v-1,cost,i});
    }
    
    // Sort edges by cost
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.cost < b.cost || (a.cost == b.cost && a.id < b.id);
    });
    
    std::vector<ll> answ(nEdges, 0); // [id] -> answ
    
    std::vector<std::vector<Edge>> tree(nVert);
    
    ll sum = 0;
    { // Construct Minimum spanning tree
        DSU dsu(nVert);
        
        std::vector<bool> included(nEdges, false);
        
        for (int i = 0; i < nEdges; ++i) {
            const auto& it = edges[i];
            if (dsu.find_set(it.u) != dsu.find_set(it.v)) {
                dsu.union_sets(it.u, it.v);
                included[it.id] = true;
                sum += it.cost;
                tree[it.u].push_back(Edge{it.u, it.v, it.cost, it.id});
                tree[it.v].push_back(Edge{it.v, it.u, it.cost, it.id});
            }
        }
        
        for (int u = 1; u < nVert; ++u) {
            assert(dsu.find_set(u-1) == dsu.find_set(u));
        }
        
        for (int i = 0; i < nEdges; ++i) {
            if (included[i]) {
                answ[i] = sum;
            }
        }
    }
    
    // Construct Sparse Table for maximum on tree:
    
    std::vector<std::vector<int>> prev(20, std::vector<int>(nVert, -1));
    std::vector<std::vector<int>> max(20, std::vector<int>(nVert));
    
    std::vector<int> depth(nVert);
    
    std::function<void(int,int,int)> visit = [&](const int curr, const int parent, const int d) {
        depth[curr] = d;
        for (auto& edge : tree[curr]) {
            if (parent != edge.v) {
                prev[0][edge.v] = curr;
                max[0][edge.v] = edge.cost;
                visit(edge.v, curr, d+1);
            }
        }
    };
    
    visit(0, -1, 0);
    
    for (int pow = 1; pow < 20; ++pow) {
        for (int u = 0; u < nVert; ++u) {
            int v = prev[pow-1][u];
            if (v != -1) {
                prev[pow][u] = prev[pow-1][v];
                max[pow][u] = std::max(max[pow-1][u], max[pow-1][v]);
            }
        }
    }
    
    // Query to sparse table on tree to get max edge on path from u to v:    
    std::function<int(int,int)> get_max = [&](int u, int v) {
        if (depth[u] > depth[v]) {
            return get_max(v, u);
        }
        assert(u != v);
        int answ = 0;
        int diff = depth[v] - depth[u];
        int pow = 0;
        while ((1 << (pow+1)) <= diff) ++pow;
        
        while (depth[v] != depth[u]) {
            assert(diff != 0);
            while (pow > 0 && diff < (1 << pow)) --pow;
            answ = std::max(answ, max[pow][v]);
            v = prev[pow][v];
            diff -= 1 << pow;
        }
        pow = 0;
        while (u != v) {
            while (pow > 0 && prev[pow][u] == prev[pow][v]) --pow;
            answ = std::max({answ, max[pow][u], max[pow][v]});
            u = prev[pow][u];
            v = prev[pow][v];
        }
        return answ;
    };
    
    // Get answer for other edges:
    for (auto& e : edges) {
        if (answ[e.id] == 0) {
            answ[e.id] = sum + e.cost - get_max(e.u, e.v);
        }
    }
    
    for (auto& it : answ) {
        std::cout << it << '\n';
    }
    
    return 0;
}