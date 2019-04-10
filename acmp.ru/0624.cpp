/*
    Задача: 624. Электронная почта
    
    Решение: графы, топологическая сортировка, циклы, O(n*log(n)+m)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define reunique(x) (x).erase(std::unique(all(x)), (x).end())
#define lowpos(x, y) int(std::lower_bound(all(x), y) - (x).begin())
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
struct Graph {
    const int n;
    vvi next;
    vi color;
    bool ok;
    Graph(int n_) : n(n_), next(n_) { }
    void add_edge(int u, int v) { next[u].push_back(v); }
    void dfs(int u) {
        color[u] = 1;
        for (int v : next[u]) {
            if (color[v] == 0) {
                dfs(v);
            } else if (color[v] == 1) {
                ok = false;
            }
        }
        color[u] = 2;
    }
    bool solve() {
        ok = true;
        color.assign(n, 0);
        for (int u = 0; u < n; ++u) {
            if (color[u] != 2) {
                dfs(u);
            }
        }
        return ok;
    }
};
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    int t; 
    while (std::cin >> t) {
        while (t--) {
            int n, m; std::cin >> n >> m;
            vvi order(n);
            vi coord;
            for (int i = 0; i < n; ++i) {
                int s; std::cin >> s;
                order[i].resize(s);
                for (auto &it : order[i]) {
                    std::cin >> it;
                    coord.push_back(std::abs(it));
                }
            }
            std::sort(all(coord));
            reunique(coord);
            Graph graph(2 * isz(coord));
            for (auto &vec : order) {
                for (int i = 0; i < isz(vec); ++i) {
                    bool send = (vec[i] > 0);
                    vec[i] = lowpos(coord, std::abs(-vec[i]));
                    if (!send) { vec[i] += isz(coord); }
                    if (i > 0) {
                        graph.add_edge(vec[i-1], vec[i]);
                    }
                }
            }
            for (int i = 0; i < isz(coord); ++i) {
                graph.add_edge(i, i + isz(coord));
            }
            std::cout << (graph.solve() ? "YES\n" : "NO\n");
        }
    }
    return 0;
}