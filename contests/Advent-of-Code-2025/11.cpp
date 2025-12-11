#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using ll = long long;
using vi = std::vector<int>;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using vvi = std::vector<vi>;
void solveEasy() {
    std::string s;
    std::string from;
    std::map<std::string, std::vector<std::string>> next;
    while (std::cin >> s) {
        assert(isz(s));
        if (s.back() == ':') {
            s.pop_back();
            from = s;
        } else {
            assert(isz(from));
            next[from].push_back(s);
        }
    }
    // пишем и запускаем dfs
    std::map<std::string, int> color;
    std::map<std::string, ll> numWays;
    std::function<ll(std::string)> dfs = [&](std::string u) -> ll {
        if (color[u] == 2)
            return numWays[u];
        assert(color[u] == 0);
        if (u == "out")
            numWays[u] += 1;
        color[u] = 1;
        for (auto v : next[u])
            if (color[v] == 1) {
                assert(false && "Cycles are prohibited!");
            } else {
                numWays[u] += dfs(v);
            }
        color[u] = 2;
        return numWays[u];
    };
    std::cout << dfs("you") << std::endl;
}

void solveHard() {
    std::string s;
    std::string from;
    std::vector<std::pair<std::string, std::string>> edges;
    std::vector<std::string> vertices;
    while (std::cin >> s) {
        assert(isz(s));
        if (s.back() == ':') {
            s.pop_back();
            from = s;
            vertices.push_back(from);
        } else {
            assert(isz(from));
            edges.emplace_back(from, s);
            vertices.push_back(s);
        }
    }
    std::sort(all(vertices));
    vertices.erase(std::unique(all(vertices)), vertices.end());
    std::map<std::string, int> vertexId;
    for (int i = 0; i < isz(vertices); i++) {
        vertexId[vertices[i]] = i;
    }
    int numVert = isz(vertices);
    vvi next(numVert);
    for (const auto &[u, v] : edges) {
        int iu = vertexId[u], iv = vertexId[v];
        next[iu].push_back(iv);
    }
    // пишем и запускаем dfs
    // s -> f, должны пройти через a и b
    vi color(numVert);
    vvl count(numVert, vl(4));
    int st = vertexId["svr"], fin = vertexId["out"];
    int a = vertexId["dac"], b = vertexId["fft"];
    std::function<vl(int)> dfs = [&](int u) -> vl {
        if (color[u] == 2)
            return count[u];
        assert(color[u] == 0);
        if (u == fin)
            count[u][0]++;
        int uMask = 0;
        if (u == a)
            uMask |= 1;
        if (u == b)
            uMask |= 2;
        color[u] = 1;
        for (auto v : next[u])
            if (color[v] == 1) {
                assert(false && "Cycles are prohibited!");
            } else {
                dfs(v);
                for (int mask = 0; mask < 4; mask++)
                    count[u][mask | uMask] += count[v][mask];
            }
        color[u] = 2;
        return count[u];
    };
    std::cout << dfs(st)[3] << std::endl;
}

main() {
    solveHard();
}
