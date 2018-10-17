/*
    Problem: 1934. Black Spot
    
    Solution: Dijkstra's shortest path, probability theory, O((n+m)*log(m))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>

typedef double Real;

struct State {

    int to, from, dist; Real prob;

};

const int INF = (int)1e9+1;

bool operator<(const State& a, const State& b) {
    if (a.dist < b.dist) return true;
    if (a.dist > b.dist) return false;
    if (a.prob > b.prob) return true;
    if (a.prob < b.prob) return false;
    return a.to < b.to || (a.to == b.to && a.from < b.from);
}

bool operator>(const State& a, const State& b) {
    return b < a;
}

bool operator==(const State& a, const State& b) {
    return !(a < b || b < a);
}

struct Edge {
    int u, v, p;
};

int main() {
    int nV, nE;
    scanf("%d %d", &nV, &nE);
    int s, t; scanf("%d %d", &s, &t);
    std::vector<std::vector<Edge>> edges(1+nV);
    for (int i = 0; i < nE; ++i) {
        int u, v, p; scanf("%d %d %d", &u, &v, &p);
        edges[u].push_back(Edge{u,v,100-p});
        edges[v].push_back(Edge{u,v,100-p});
    }
    std::vector<int> dist(1+nV, INF), from(1+nV); 
    std::vector<Real> prob(1+nV, 0);
    std::priority_queue<State, std::vector<State>, std::greater<State>> queue;
    queue.push(State{s,0,0,Real(1)});
    while (!queue.empty()) {
        auto state = queue.top(); queue.pop();
        int u = state.to;
        if (dist[u] < state.dist || (dist[u] == state.dist && prob[u] > state.prob)) {
            continue;
        }
        dist[u] = state.dist;
        prob[u] = state.prob;
        from[u] = state.from;
        for (auto& e : edges[u]) {
            int v = e.u + e.v - u;
            Real p = e.p / Real(100);
            if (dist[v] > dist[u] + 1 || (dist[v] == dist[u] + 1 && prob[v] < prob[u] * p)) {
                queue.push(State{v,u,dist[u]+1,prob[u] * p});
            }
        }
    }
    assert(dist[t] != INF);
    printf("%d %0.6f\n", dist[t]+1, 1.0-prob[t]);
    std::vector<int> path{t};
    while (t != s) {
        t = from[t];
        path.push_back(t);
    }
    std::reverse(path.begin(), path.end());
    for (auto& it : path) {
        printf("%d ", it);
    }
    return 0;
}