/*
    Problem: 691D. Swaps in Permutation
    
    Solution: graphs, bfs, sorting, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cassert>

struct Edge {
    int u, v;
};

inline bool operator<(const Edge& a, const Edge& b) {
    return a.u < b.u || (a.u == b.u && a.v < b.v);
}

inline bool operator==(const Edge& a, const Edge& b) {
    return !(a < b) && !(b < a);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nItems, nEdges;
    std::cin >> nItems >> nEdges;
    
    std::vector<int> arr(nItems);
    for (auto& it : arr) std::cin >> it;
    
    // Input edges:
    std::vector<Edge> list;
    for (int i = 0; i < nEdges; ++i) {
        int a, b; std::cin >> a >> b; --a, --b;
        if (a > b) std::swap(a, b);
        list.push_back(Edge{a,b});
    }
    std::sort(list.begin(), list.end());
    list.erase(std::unique(list.begin(), list.end()), list.end());
    
    std::vector<std::vector<int>> edges(nItems);
    for (auto& it : list) {
        edges[it.u].push_back(it.v);
        edges[it.v].push_back(it.u);
    }
    
    // Find connectivity components:
    std::vector<int> part(nItems, 0);
    int nParts = 0;
    for (int i = 0; i < nItems; ++i) {
        if (part[i] == 0) {
            part[i] = ++nParts;
            std::queue<int> queue;
            queue.push(i);
            while (!queue.empty()) {
                auto curr = queue.front(); queue.pop();
                for (auto next : edges[curr]) {
                    if (part[next] == 0) {
                        part[next] = part[curr];
                        queue.push(next);
                    }
                }
            }
        }
    }
    std::vector<std::vector<int>> parts(1+nParts);
    for (int i = 0; i < nItems; ++i) {
        parts[part[i]].push_back(arr[i]);
    }
    // Sort values in every connectivity component:
    for (auto& it : parts) {
        std::sort(it.begin(), it.end(), std::greater<int>());
    }
    // Put sorted values in array and output:
    for (int i = nItems-1; i >= 0; --i) {
        int v = parts[part[i]].back();
        parts[part[i]].pop_back();
        arr[i] = v;
    }
    for (auto& it : arr) {
        std::cout << it << ' ';
    }
    return 0;
}