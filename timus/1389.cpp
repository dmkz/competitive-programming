/*
    Problem: 1389. Roadworks
    Solution: trees, dynamic programming, dfs, O(n)
*/

#include <bits/stdc++.h>
#define isz(x) (int)(x).size()

struct Edge {
    int u, v;
};

struct State {
    int size{0}, edge{-1};
};

bool operator<(State a, State b) {
    return a.size < b.size || (a.size == b.size && a.edge < b.edge);
}

const int NMAX = 100100;
std::vector<Edge> edges, answ;
std::vector<int> adj[NMAX], stack;
State dp[2][NMAX];

void dfs(int u, int p = 0) {
    // решим задачу для поддеревьев рекурсивно:
    for (int id : adj[u]) {
        const auto &e = edges[id];
        const int v = e.u + e.v - u;
        if (v == p) continue;
        dfs(v, u);
    }
    // теперь переберем то ребро, выходящее из u, которое возьмем
    // dp[1][u] - лучший ответ, если мы берем какое-нибудь ребро из u
    // dp[0][u] - лучший ответ, если мы не берем никакого ребра из u
    // пусть мы возьмем ребро u-v, тогда для v мы не можем больше брать никакого ребра: dp[0][v]
    // а для всех остальных мы можем брать ребро, то есть, сумма dp[1][w], где w - потомок u, отличный от v
    // лучший ответ для dp[1][u] это dp[0][v] + сумма dp[1][w] + 1
    // лучший ответ для dp[0][u] это сумма dp[1][w]
    // будем запоминать ребро, которое взяли, то есть, ребро u-v, дающее максимальный ответ
    stack = {0};
    for (int id : adj[u]) {
        const auto &e = edges[id];
        const int v = e.u + e.v - u;
        if (v == p) continue;
        stack.push_back(stack.back() + dp[1][v].size);
    }
    dp[0][u].size = stack.back();
    int sum = 0;
    for (int i = isz(adj[u])-1; i >= 0; i--) {
        const int id = adj[u][i];
        const auto & e = edges[id];
        const int v = e.u + e.v - u;
        if (v == p) continue;
        stack.pop_back();
        dp[1][u] = std::max(dp[1][u], State{sum + 1 + dp[0][v].size + stack.back(), id});
        sum += dp[1][v].size;
    }
}
void find(int can_take, int u, int p = 0) {
// восстанавливаем ответ
// переберем все исходящие ребра, если мы в динамике взяли ребро (u,v), то добавляем его к ответу
// вызываемся рекурсивно от всех поддеревьев: в поддереве с корнем v из v мы больше не можем брать никакого ребра
// в остальных поддеревьях можем
    for (int id : adj[u]) {
        const auto & e = edges[id];
        const int v = e.u + e.v - u;
        if (v == p) continue;
        if (id == dp[can_take][u].edge) {
            answ.push_back(edges[id]);
            find(false, v, u);
        } else find(true, v, u);
    }
}
int main() {
    int n, m; scanf("%d %d", &n, &m);
    assert(n-1 == m);
    for (int id = 0, u, v; id < m; id++) {
        scanf("%d %d", &u, &v);
        edges.push_back({u,v});
        adj[u].push_back(id);
        adj[v].push_back(id);
    }
    dfs(1);
    find(true, 1);
    printf("%d\n", isz(answ));
    for (auto e : answ) printf("%d %d\n", e.u, e.v);
    return 0;
}