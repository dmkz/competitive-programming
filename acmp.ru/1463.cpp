/*
    Задача: 1463. Повышение квалификации
    Решение: dfs, bfs, euler tour, binary search, std::set, sorting, queries offline, two pointers, O(n+q*(log(n)+log(q)))
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using vi = std::vector<int>;
using vvi = std::vector<vi>;
const auto io_sync_off = [](){std::ios_base::sync_with_stdio(0);std::cin.tie(0);return 0;}();
int main() {
    // Input:
    int nVert; std::cin >> nVert;
    vvi next(1+nVert);
    for (int u = 2, p; u <= nVert; u++) {
        std::cin >> p; 
        next[p].push_back(u);
    }
    // dfs:
    vi tin(1+nVert), tout(1+nVert), depth(1+nVert);
    int timer = 0;
    std::function<void(int)> dfs = [&](int u) {
        tin[u] = timer++;
        for (int v : next[u]) {
            depth[v] = depth[u] + 1;
            dfs(v);
        }
        tout[u] = timer++;
    };
    dfs(1);
    // bfs:
    vi arr_tin, arr_depth, arr_vert;
    std::queue<int> queue;
    queue.push(1);
    while (isz(queue)) {
        int u = queue.front(); queue.pop();
        arr_tin.push_back(tin[u]);
        arr_depth.push_back(depth[u]);
        arr_vert.push_back(u);
        for (int v : next[u]) {
            queue.push(v);
        }
    }
    // Queries:
    int nQ; std::cin >> nQ;
    struct Query { int left, right; };
    std::vector<Query> queries(nQ);
    for (int i = 0; i < nQ; i++) {
        int u, d; std::cin >> u >> d;
        d += depth[u];
        auto begin = arr_tin.begin() + int(std::lower_bound(all(arr_depth), d) - arr_depth.begin());
        auto after = arr_tin.begin() + int(std::upper_bound(all(arr_depth), d) - arr_depth.begin());
        begin = std::lower_bound(begin, after, tin[u]);
        after = std::lower_bound(begin, after, tout[u]);
        queries[i] = Query{int(begin-arr_tin.begin()), int(after-arr_tin.begin())-1};
    }
    std::sort(all(queries),[](auto a, auto b){return a.right-a.left < b.right-b.left;});
    // Processing queries:
    vi color(1+nVert);
    int nColors = 0;
    std::set<int> set;
    for (auto &q : queries) {
        auto rt = set.upper_bound(q.right);
        auto lt = set.lower_bound(q.left);
        if (rt == lt) {
            nColors++;
            set.insert(q.left);
            set.insert(q.right);
            for (int i = q.left; i <= q.right; i++) {
                const int vert = arr_vert[i];
                assert(color[vert] == 0);
                color[vert] = nColors;
            }
        }
    }
    // Two pointers
    vi count(1+nColors, 0); count[0]++;
    int lt = 1, rt = 0, left = 1, right = nVert, used = 1;
    while (lt <= nVert) {
        while (rt + 1 <= nVert && used != isz(count)) {
            const int c = color[++rt];
            used += (++count[c] == 1);
        }
        if (used == isz(count)) {
            if (right - left > rt - lt) {
                left = lt;
                right = rt;
            }
        }
        const int c = color[lt++];
        used -= (--count[c] == 0);
    }
    std::cout << left << ' ' << right << std::endl;
    return 0;
}