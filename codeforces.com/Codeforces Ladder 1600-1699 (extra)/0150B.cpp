/*
    Problem: 150B. Quantity of Strings
    
    Solution: dsu, math, combinatorics, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

typedef std::vector<int> vi;

const int mod = (int)1e9+7;

struct DSU {
    vi parent, size;
    
    DSU(int n) : parent(n, 0), size(n, 1) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    
    int get_parent(int u) {
        return parent[u] == u ? u : parent[u] = get_parent(parent[u]);
    }
    
    void union_sets(int u, int v) {
        u = get_parent(u);
        v = get_parent(v);
        if (u != v) {
            if (size[u] < size[v]) std::swap(u, v);
            parent[v] = u;
            size[u] += v;
        }
    }
    
};

int pow(int a, int n) {
    int r = 1;
    while (n > 0) {
        if (n & 1) {
            r = int(1LL * r * a % mod);
        }
        a = int(1LL * a * a % mod);
        n >>= 1;
    }
    return r;
}

int solve(int n, int len, int nAlp) {
    DSU dsu(n);
    for (int i = 0; i + len - 1 < n; ++i) {
        for (int lt = i, rt = i + len - 1; lt <= rt; ++lt, --rt) {
            dsu.union_sets(lt, rt);
        }
    }
    vi arr;
    for (int i = 0; i < n; ++i) {
        arr.push_back(dsu.get_parent(i));
    }
    std::sort(arr.begin(), arr.end());
    arr.erase(std::unique(arr.begin(), arr.end()), arr.end());
    return pow(nAlp, (int)arr.size());
}

int main() {
    int n, len, nAlp;
    while (std::cin >> n >> nAlp >> len) {
        std::cout << solve(n, len, nAlp) << std::endl;
    }
    return 0;
}