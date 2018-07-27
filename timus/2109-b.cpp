/*
    Problem: 2109. Tourism on Mars
    
    Solution: DFS, LCA, Sparse Table, O(n log(n) + q)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

//#pragma GCC optimize("O3")
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <cassert>

struct Node {
    int min, value;
};

inline Node combine(const Node& a, const Node& b) {
    return a.min <= b.min ? a : b;
}

struct SparseTable {
    
    static std::vector<int> log2;
    
    std::vector<std::vector<Node>> data;
    
    SparseTable() { }
    
    SparseTable(const std::vector<Node>& arr) { build(arr); }
    
    void build(const std::vector<Node>& arr) {
        assert(!log2.empty());
        data.clear();
        const int n = (int)arr.size();
        for (int i = (int)log2.size(); i <= n; ++i) {
            log2.push_back(log2[i / 2]+1);
        }
        data.reserve(log2[n]+1);
        data.push_back(arr);
        for (int pow = 1, len = 1; 2 * len <= n; ++pow, len *= 2) {
            data.push_back(std::vector<Node>(n-2*len+1));
            for (int pos = 0; pos + 2 * len <= n; ++pos) {
                data[pow][pos] = combine(
                    data[pow-1][pos], data[pow-1][pos+len]
                );
            }
        }
    }
       
    inline int get(int l, int r) const {
        const int level = log2.at(r-l+1);
        return combine(data[level][l], data[level][r-(1 << level)+1]).value;
    }
};

std::vector<int> SparseTable::log2{0,0};

int main() {
    int n;
    scanf("%d", &n);
    
    std::vector<std::vector<int>> edges(n);

    for (int i = 1; i < n; ++i) {
        int a, b; 
        scanf("%d %d", &a, &b);
        --a, --b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    
    // DFS: get parent and depth of each vertex
    std::vector<int> depth(n, -1);
    std::vector<std::vector<int>> parent(20, std::vector<int>(n, -1));
    
    std::function<void(int,int,int)> visit = [&](const int curr, const int par, const int d) {
        parent[0][curr] = par;
        depth[curr] = d;
        for (auto next : edges[curr]) {
            if (next != par) {
                visit(next, curr, d+1);
            }
        }
    };
    
    visit(0, -1, 0); // run dfs from root
    
    // Construct Sparse Table for lca:
    for (int pow = 1; pow < 20; ++pow) {
        for (int u = 0; u < n; ++u) {
            int v = parent[pow-1][u];
            if (v == -1) continue;
            parent[pow][u] = parent[pow-1][v];
        }
    }
    
    // Function for getting lca of two vertices
    std::function<int(int,int)> lca = [&](int v1, int v2) {
        if (depth[v1] < depth[v2]) return lca(v2, v1);
        int pow = 0;
        while (depth[v1] != depth[v2]) {
            assert(pow >= 0);
            int par = parent[pow][v1];
            if (par == -1 || depth[par] < depth[v2]) {
                pow--;
            } else {
                v1 = par;
                pow++;
            }
        }
        pow = 0;
        while (v1 != v2) {
            assert(pow >= 0);
            int p1 = parent[pow][v1];
            int p2 = parent[pow][v2];
            if (p1 == p2 && pow > 0) {
                --pow;
            } else {
                v1 = p1;
                v2 = p2;
                ++pow;
            }
        }
        return v1;
    };
    
    // Construct Sparse Table on array of nodes {depth, vertex} for getting vertex with min depth
    std::vector<Node> arr;
    for (int i = 0; i+1 < n; ++i) {
        int lca_ = lca(i, i+1);
        arr.push_back(Node{depth[lca_], lca_+1});
    }
    
    SparseTable st(arr);
    
    // Answer to queries
    int nQueries;
    scanf("%d", &nQueries);
    
    while (nQueries--) {
        int u, v; 
        scanf("%d %d", &u, &v);
        --u, --v;
        if (u == v) {
            printf("%d\n",u+1);
            continue;
        }
        if (u > v) {
            std::swap(u, v);
        }
        printf("%d\n", st.get(u, v-1));
    }
    
    return 0;
}