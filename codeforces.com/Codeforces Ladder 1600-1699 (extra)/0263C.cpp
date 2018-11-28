/*
    Problem: 263C. Circle of Numbers
    
    Solution: constructive, graphs, O(n*log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

#define all(x) (x).begin(), (x).end()
#define unique(x) (x).erase(std::unique(all(x)), (x).end())

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

bool check(int n, const vi cand, const vvi& edges) {
    vi adj(4);
    for (int p = 0; p < n; ++p) {
        adj[0] = cand[(p-1+n)%n];
        adj[1] = cand[(p-2+n)%n];
        adj[2] = cand[(p+1+n)%n];
        adj[3] = cand[(p+2+n)%n];
        std::sort(all(adj));
        if (adj != edges[cand[p]]) {
            return false;
        }
    }
    return true;
}

vi brute(int n, const vvi& edges) {
    vi arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = i+1;
    }
    do {
        if (check(n,arr,edges)) {
            return arr;
        }
    } while (std::next_permutation(all(arr)));
    return {-1};
}

vi solve(int n, const vvi& edges) {
    for (int u = 1; u <= n; ++u) {
        if ((int)edges[u].size() != 4u) {
            return {-1};
        }
    }
    vi used(1+n), arr(n); int nUsed = 0;
    arr[1] = 1, used[1] = 1, nUsed++;
    for (int u : edges[1]) {
        int cnt = 0;
        for (int v : edges[u]) {
            if (v == 1) continue;
            cnt += (std::find(all(edges[1]), v) == edges[1].end());
        }
        if (cnt == 1) {
            int p = -1;
            if (!arr[0]) {
                p = 0;
            } else if (!arr[2]) {
                p = 2;
            } else {
                return {-1};
            }
            arr[p] = u, used[u] = 1, nUsed++;
        }
    }
    if (nUsed != 3) {
        return {-1};
    }
    for (int p = 2; p+1 < n; ++p) {
        int curr = arr[p], prev = arr[p-1], next = -1;
        for (int u : edges[curr]) {
            if (used[u]) {
                continue;
            }
            if (std::find(all(edges[prev]), u) != edges[prev].end()) {
                next = u;
                break;
            }
        }
        if (next == -1) {
            return {-1};
        }
        arr[p+1] = next, used[next] = true, nUsed++;
    }
    if (!check(n,arr,edges)) {
        return {-1};
    }
    return arr;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        vvi edges(1+n);
        for (int i = 0, u, v; i < 2 * n; ++i) {
            std::cin >> u >> v;
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
        for (int i = 1; i <= n; ++i) {
            std::sort(all(edges[i]));
            unique(edges[i]);
        }
        auto answ = n <= 8 ? brute(n, edges) : solve(n, edges);
        for (auto it : answ) {
            std::cout << it << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}