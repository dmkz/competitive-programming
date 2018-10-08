/*
    Problem: 246E. Blood Cousins Return
    
    Solution: euler tour, trees, dfs, bfs, Mo's algorithm, O(n * (log(n) + sqrt(q)))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#include <cassert>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

struct Query {
    int l, r, id;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    // Input:
    int n; std::cin >> n;
    vi item(1+n), tin(1+n,-1), tout(1+n,-1), parent(1+n), depth(1+n), height(1+n); 
    vvi edges(1+n);
    {
        std::vector<std::pair<std::string, int>> input(n);
        std::vector<std::string> names;
        for (auto& rec : input) {
            std::cin >> rec.first >> rec.second;
            names.push_back(rec.first);
        }
        // Add edges in graph:
        std::sort(names.begin(), names.end());
        names.erase(std::unique(names.begin(), names.end()), names.end());
        for (int i = 0; i < n; ++i) {
            item[i+1] = int(std::lower_bound(names.begin(), names.end(), input[i].first)-names.begin());
            int p = input[i].second, v = i+1;
            parent[v] = p;
            edges[p].push_back(v);
            edges[v].push_back(p);
        }
    }
    { // DFS:
        int timer = 0;
        std::function<void(int,int)> visit = [&](int u, int p) {
            assert(u == 0 || parent[u] == p);
            tin[u] = timer++;
            height[u] = 1;
            for (auto v : edges[u]) {
                if (v == p) continue;
                visit(v,u);
                height[u] = std::max(height[u], height[v]+1);
            }
            tout[u] = timer++;
        };
        visit(0,-1);
    }
    vi level_begin(n+2, n+1), arr, order;
    { // BFS:
        std::queue<int> queue;
        queue.push(0);
        while (!queue.empty()) {
            auto curr = queue.front(); queue.pop();
            order.push_back(curr);
            level_begin[depth[curr]] = std::min(level_begin[depth[curr]], (int)arr.size());
            arr.push_back(item[curr]);
            for (auto next : edges[curr]) {
                if (next == parent[curr]) continue;
                depth[next] = depth[curr]+1;
                queue.push(next);
            }
        }
    }
    // Input Queries:
    int nQueries;
    std::cin >> nQueries;
    std::vector<Query> queries;
    vi answ(nQueries);
    for (int i = 0; i < nQueries; ++i) {
        int u, k; std::cin >> u >> k;
        k += depth[u];
        if (k >= height[u]+depth[u]) { continue; }
        // find `left` and `right` position in array of bfs order for childrens of vertex `u` on depht `k`
        int left = -1, right = -1;
        {
            int low = level_begin[k]-1, high = level_begin[k+1];
            while (high - low > 1) {
                int mid = (low + high) / 2;
                if (tin[order[mid]] > tin[u]) {
                    high = mid;
                } else {
                    low = mid;
                }
            }
            left = high;
        }
        {
            int low = left, high = level_begin[k+1];
            while (high - low > 1) {
                int mid = (low + high) / 2;
                if (tout[order[mid]] < tout[u]) {
                    low = mid;
                } else {
                    high = mid;
                }
            }
            right = low;
        }
        assert(left != -1 && right != -1 && right <= n);
        queries.push_back(Query{left, right, i});
    }
    // Mo's algorithm:
    const int GSIZE = 256;
    std::stable_sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {
        if (a.l / GSIZE != b.l / GSIZE) {
            return a.l < b.l;
        } else {
            return a.r < b.r;
        }
    });
    
    int l = 0, r = -1, curr = 0; vi count(n);
    for (auto& q : queries) {
        while (r < q.r) {
            ++r;
            count[arr[r]]++;
            curr += (count[arr[r]] == 1);
        }
        while (l < q.l) {
            count[arr[l]]--;
            curr -= (count[arr[l]] == 0);
            l++;
        }
        while (l > q.l) {
            --l;
            count[arr[l]]++;
            curr += (count[arr[l]] == 1);
        }
        while (r > q.r) {
            count[arr[r]]--;
            curr -= (count[arr[r]] == 0);
            r--;
        }
        answ[q.id] = curr;
    }
    // Output:
    for (auto& it : answ) std::cout << it << '\n';
    return 0;
}