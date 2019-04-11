/*
    Задача: 746. Гонки
    
    Решение: графы, комбинаторика, O(n^3)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m;
    while (std::cin >> n >> m) {
        vvi adj(1+n);
        while (m--) {
            int u, v; std::cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vi cnt(1+n);
        auto calc = [&](int u, int v) {
            int ret = 0;
            for (int next : adj[u]) {
                cnt[next]++; 
            }
            for (int next : adj[v]) {
                cnt[next]++;
                ret += (cnt[next] == 2);
            }
            ret -= (cnt[u] == 2);
            ret -= (cnt[v] == 2);
            for (int next : adj[v]) { cnt[next]--; }
            for (int next : adj[u]) { cnt[next]--; }
            return ret;
        };
        int64_t answ = 0;
        for (int u = 1; u <= n; ++u) {
            for (int v = u+1; v <= n; ++v) {
                int ret = calc(u,v);
                answ += ret * (ret-1) / 2;
            }
        }
        std::cout << answ / 2 << std::endl;
    }
    return 0;
}