/*
    Problem: 375D. Tree and Queries
    
    Solution: euler tour, mo's algorithm, O(n sqrt(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <functional>

struct Query { // record for one query
    int l, r, k, id;
};

struct Statistic { // statistics on segment of array: insert / remove color in O(1), answer in O(1)
    
    std::vector<int> count; // count[color]
    
    std::vector<int> suff;  // suff[k] = number of colors: count[color] >= k
    
    Statistic(const int mxColor) {
        count.assign(1+mxColor, 0);
        suff.push_back(mxColor);
    }
    
    void insert(const int color) {
        auto& cnt = count[color];
        cnt++;
        if (cnt >= (int)suff.size()) suff.push_back(0);
        suff[cnt]++;
    }
    
    void remove(const int color) {
        auto& cnt = count[color];
        suff[cnt]--;
        cnt--;
        if (suff.back() == 0) suff.pop_back();
    }
    
    inline int answer(const int k) const {
        return k < (int)suff.size() ? suff[k] : 0;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    // Input colors and edges:    
    int nVert, nQueries;
    std::cin >> nVert >> nQueries;
    
    std::vector<int> color(nVert);
    
    for (auto& c : color) {
        std::cin >> c;
    }
    
    std::vector<std::vector<int>> edges(nVert);
    
    for (int i = 1; i < nVert; ++i) {
        int a, b; std::cin >> a >> b; --a, --b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    
    // ---------------- Euler tour on tree ----------------
    
    std::vector<int> arr;
    
    std::vector<Query> queries;
    
    { 
        std::vector<int> l(nVert), r(nVert);    
        
        std::function<void(int,int)> visit = [&](const int curr, const int parent) {
            arr.push_back(color[curr]);
            l[curr] = (int)arr.size()-1;
            for (auto next : edges[curr]) {
                if (next == parent) continue;
                visit(next, curr);
            }
            r[curr] = (int)arr.size()-1;
        };
        
        visit(0, -1); // run dfs
        
        // Input queries:
        for (int i = 0; i < nQueries; ++i) {
            int v, k;
            std::cin >> v >> k;
            --v;
            queries.push_back(Query{l[v], r[v], k, i});
        }
    }
    
    // -------------- Mo algorithm --------------
    
    const int GSIZE = 512;
    // Sorting queries:
    std::stable_sort(queries.begin(), queries.end(), [](const Query& a, const Query& b){
        if (a.l / GSIZE != b.l / GSIZE) {
            return a.l < b.l;
        }
        return a.r < b.r;
    });
    
    // Create statistic object:
    Statistic stat(*std::max_element(color.begin(), color.end()));
    
    // Prepare vector for answers:
    std::vector<int> answer(nQueries);
    
    // Queries processing:
    int l = 0, r = -1;
    
    for (auto& q : queries) {
        while (r < q.r) stat.insert(arr[++r]);
        while (l < q.l) stat.remove(arr[l++]);
        while (l > q.l) stat.insert(arr[--l]);
        while (r > q.r) stat.remove(arr[r--]);
        answer[q.id] = stat.answer(q.k);
    }
    
    // Output:
    for (auto it : answer) {
        std::cout << it << '\n';
    }
    
    return 0;
}