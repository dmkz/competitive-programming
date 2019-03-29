/*
    Задача: 226. Перегоны
    
    Решение: поиск в ширину, граф, восстановление графа, O(n^3)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define size(x) (int)(x).size()
typedef long long ll;
const ll UNDEF = LLONG_MIN;
struct Edge { int u, v; ll w; };
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<ll> vl;
typedef std::vector<vl> vvl;
typedef std::vector<Edge> ve;
void assert_tle(bool q) {
    while (!q);
}
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    int nV, nE;
    std::cin >> nV >> nE;
    vvi adj(nV);
    ve edges;
    bool ok = true;
    for (int i = 0, u, v; i < nE; ++i) {
        std::cin >> u >> v; u--,v--;
        std::string s; std::cin >> s;
        assert_tle(size(s) <= 14);
        ll fi = 0, se = 0;
        auto pos = s.find('.');
        if (pos == std::string::npos) {
            fi = std::stoll(s);
            se = 0;
        } else {
            fi = std::stoll(s.substr(0,pos));
            int cnt = 0;
            for (int j = (int)pos+1; j < size(s); ++j) {
                se *= 10;
                se += (s[j] - '0');
                ++cnt;
            }
            while (cnt < 3) {
                se *= 10;
                cnt++;
            }
        }
        assert_tle(se < 1000);
        ll w = fi * 1000 + se;
        assert(w <= 1000LL * 1000LL * 1000LL * 1000LL * 1000LL);
        edges.push_back(Edge{u,v,w});
        adj[u].push_back(size(edges)-1);
        adj[v].push_back(size(edges)-1);
        if (u == v && w != 0) {
            ok = false;
        }
    }
    if (!ok) { 
        // assert(false); RE4
        std::cout << "NO\n"; return 0; 
    }
    vvl dist(nV, vl(nV, UNDEF));
    for (int i = 0; i < nV; ++i) {
        dist[i][i] = 0;
    }
    std::queue<int> queue;
    queue.push(0);
    while (!queue.empty()) {
        auto u = queue.front(); queue.pop();
        assert(dist[0][u] != UNDEF);
        for (int id : adj[u]) {
            const auto& e = edges[id];
            int v = e.u + e.v - u;
            if (u != v && dist[0][v] == UNDEF) {
                dist[0][v] = dist[0][u] + (v < u ? -e.w : e.w);
                queue.push(v);
            }
        }
    }
    for (int u = 1; u < nV; ++u) {
        if (dist[0][u] < 0) {
            // assert(false); RE2
            std::cout << "NO\n"; 
            return 0;
        }
    }
    for (int u = 0; u < nV; ++u) {
        for (int v = u; v < nV; ++v) {
            if (dist[0][u] > dist[0][v]) {
                assert(false);
                std::cout << "NO\n"; 
                return 0;
            }
        }
    }
    for (int u = 1; u < nV; ++u) {
        for (int v = u+1; v < nV; ++v) {
            dist[u][v] = dist[0][v] - dist[0][u];
        }
    }
    for (int u = 0; u < nV; ++u) {
        for (int v = u+1; v < nV; ++v) {
            dist[v][u] = dist[u][v];
            /* WA14
            if (dist[u][v] == 0) {
                //assert(false);
                std::cout << "NO\n";
                return 0;
            }
            */
        }
    }
    for (int u = 0; u < nV; ++u) {
        for (int v = 0; v < nV; ++v) {
            if (dist[u][v] < 0) {
                //assert(false);
                std::cout << "NO\n";
                return 0;
            }
            for (int w = u; w <= v; ++w) {
                if (dist[u][w] + dist[w][v] != dist[u][v]) {
                    //assert(false);
                    std::cout << "NO\n";
                    return 0;
                }
            }
        }
        if (dist[u][u] != 0) {
            // assert(false);
            std::cout << "NO\n";
            return 0;
        }
    }
    for (auto &e : edges) {
        if (dist[e.u][e.v] != e.w) {
            //assert(false);
            std::cout << "NO\n";
            return 0;
        }
    }
    std::cout << "YES\n";
    for (int u = 0; u + 1 < nV; ++u) {
        ll d = dist[u][u+1];
        std::cout 
            << d / 1000 
            << '.' << std::setw(3) << std::setfill('0') << d % 1000
            << std::setfill(' ') << ' ';
    }
    return 0;
}