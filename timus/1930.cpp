/*
    Problem: 1930. Ivan's Car
    
    Solution: graphs, bfs, 0-1 edges, O(n+m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <deque>
#include <algorithm>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<vvi> vvvi;
const int INF = (int)1e9+7;
struct State {
    int dir, vert;
};

int main() {
    int nVert, nEdges;
    scanf("%d %d", &nVert, &nEdges);
    vvvi next(2, vvi(1+nVert));
    for (int i = 0; i < nEdges; ++i) {
        int u, v; scanf("%d %d", &u, &v);
        next[0][u].push_back(v);
        next[1][v].push_back(u);
    }
    int s, t;
    scanf("%d %d", &s, &t);
    vvi dist(2, vi(1+nVert, INF));
    dist[0][s] = dist[1][s] = 0;
    std::deque<State> queue;
    queue.push_back(State{0,s});
    queue.push_back(State{1,s});
    while (!queue.empty()) {
        auto u = queue.front(); queue.pop_front();
        for (auto v : next[u.dir][u.vert]) {
            if (dist[u.dir][v] > dist[u.dir][u.vert]) {
                dist[u.dir][v] = dist[u.dir][u.vert];
                queue.push_front(State{u.dir, v});
            }
        }
        for (auto v : next[1-u.dir][u.vert]) {
            if (dist[1-u.dir][v] > dist[u.dir][u.vert] + 1) {
                dist[1-u.dir][v] = dist[u.dir][u.vert] + 1;
                queue.push_back(State{1-u.dir,v});
            }
        }
    }
    printf("%d\n", std::min(dist[0][t], dist[1][t]));
    return 0;
}