/*
    Problem: 229B. Planets
    
    Solution: Dijkstra's algorithm, greedy, dynamic programming, binary search, priority queue, O((n+m)*(log(n)+log(m)))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

typedef long long ll;

const ll INF = (ll)1e18L;

struct Edge {
    int from, to; ll time;
};

bool operator<(const Edge& a, const Edge& b) {
    if (a.time < b.time) return true;
    if (a.time > b.time) return false;
    return a.from < b.from || (a.from == b.from && a.to < b.to);
}

bool operator>(const Edge& a, const Edge& b) {
    return b < a;
}

struct PlanetManager {

    std::vector<ll> time, delay;
    
    PlanetManager(const std::vector<ll>& list = {}) : time(list) {
        const int n = (int)list.size();
        delay.assign(n, 1);
        for (int i = n-2; i >= 0; --i) {
            if (time[i]+1 == time[i+1]) {
                delay[i] = delay[i+1]+1;
            } else {
                delay[i] = 1;
            }
        }
    }

    ll getDelay(ll tArrival) const {
        auto it = std::lower_bound(time.begin(), time.end(), tArrival);
        if (it == time.end() || *it != tArrival) {
            return 0;
        }
        return delay[int(it-time.begin())];
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n, m;
    while (std::cin >> n >> m) {
        std::vector<std::vector<Edge>> edges(1+n);
        for (int i = 0; i < m; ++i) {
            int u, v; ll t; std::cin >> u >> v >> t;
            edges[u].push_back(Edge{u,v,t});
            edges[v].push_back(Edge{v,u,t});
        }
        std::vector<PlanetManager> planets(1+n);
        for (int idPlanet = 1; idPlanet <= n; ++idPlanet) {
            int cnt; std::cin >> cnt;
            std::vector<ll> time(cnt);
            for (auto& it : time) { std::cin >> it; }
            planets[idPlanet] = PlanetManager(time);
        }
        std::vector<ll> minTime(1+n, INF);
        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> queue;
        queue.push(Edge{0, 1, 0});
        while (!queue.empty()) {
            auto temp = queue.top(); queue.pop();
            int prev = temp.from, curr = temp.to; ll time = temp.time;
            if (minTime[curr] <= time) {
                continue;
            }
            minTime[curr] = time;
            time += planets[curr].getDelay(time);
            for (const auto& e : edges[curr]) {
                int next = e.to;
                ll nextTime = time+e.time;
                if (minTime[next] > nextTime) {
                    queue.push(Edge{curr, next, nextTime});
                }
            }
        }
        ll answ = (minTime[n] == INF) ? -1 : minTime[n];
        std::cout << answ << std::endl;
    }
    return 0;
}