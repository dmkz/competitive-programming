/*
    Problem: 473D. The Child and Zoo
    
    Solution: DSU, combinatorics, sorting, graphs, connected components, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cassert>

typedef long long ll;
typedef long double Real;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

struct DSU {
    vi parent, size;
    DSU (int nItems) : parent(1+nItems, -1), size(1+nItems,1) {
        for (int i = 1; i <= nItems; ++i) {
            parent[i] = i;
        }
    }
    int get_parent(int i) {
        return parent[i] == i ? i : parent[i] = get_parent(parent[i]);
    }
    int get_size(int i) {
        return size[get_parent(i)];
    }
    void union_sets(int a, int b) {
        a = get_parent(a);
        b = get_parent(b);
        if (a != b) {
            if (size[a] < size[b]) std::swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};

struct Pair {
    int vert, number;
};

bool operator<(const Pair& a, const Pair& b) {
    return a.number < b.number || (a.number == b.number && a.vert < b.vert);
}

bool operator>(const Pair& a, const Pair& b) {
    return b < a;
}

bool operator==(const Pair& a, const Pair& b) {
    return !(a < b || b < a);
}

Real solve(const int nV, const vi& arr, const vvi& next) {
    // Sorting all vertices as pairs {vert, number} in not ascending order:
    ll answ = 0;
    std::vector<Pair> pairs;
    for (int i = 1; i <= nV; ++i) {
        pairs.push_back(Pair{i, arr[i]});
    }
    std::stable_sort(pairs.begin(), pairs.end(), std::greater<Pair>());
    // Add each vertex with its edges to graph and counting all paths, which pass through current vertex
    DSU dsu(nV);
    vi added(1+nV, false);
    for (const auto& curr : pairs) {
        std::vector<Pair> parts;
        for (auto v : next[curr.vert]) {
            if (added[v]) {
                parts.push_back(Pair{dsu.get_parent(v), dsu.get_size(v)});
            }
        }
        std::sort(parts.begin(), parts.end());
        parts.erase(std::unique(parts.begin(), parts.end()), parts.end());
        ll sum = 0;
        for (auto& it : parts) {
            sum += it.number;
        }
        ll mul = 2 * sum;
        for (auto& part : parts) {
            mul += (sum - part.number) * part.number;
        }
        for (auto v : next[curr.vert]) {
            if (added[v]) {
                dsu.union_sets(v, curr.vert);
            }
        }
        added[curr.vert] = true;
        answ += mul / 2 * curr.number;
    }
    return Real(2 * answ) / (Real(nV) * (nV-1));
}

int main() {
    std::cout << std::fixed << std::setprecision(4);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int nV, nE;
    while (std::cin >> nV >> nE) {
        vi arr(1+nV);
        for (int i = 1; i <= nV; ++i) {
            std::cin >> arr[i];
        }
        vvi next(1+nV);
        for (int i = 1, u, v; i <= nE; ++i) {
            std::cin >> u >> v;
            next[u].push_back(v);
            next[v].push_back(u);
        }
        std::cout << solve(nV, arr, next) << std::endl;
    }
    return 0;
}