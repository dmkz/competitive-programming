#include <bits/stdc++.h>
#define int ll
#define all(x) (x).begin(),(x).end()
using ll = long long;
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
using vvpii = std::vector<vpii>;
struct Point {
    int x, y, z, id;
};
void solve() {
    int n; std::cin >> n;
    std::vector<Point> pts(n);
    for (int i = 0; auto &[x, y, z, id] : pts) {
        std::cin >> x >> y >> z;
        id = i++;
    }
    // сортируем по каждой координате и проводим рёбра в соседей
    vvpii adj(n);
    {
        // сортируем по Ox и проводим рёбра между соседями:
        std::stable_sort(all(pts), [](const Point &a, const Point &b){
            return a.x < b.x;
        });
        for (int i = 0; i + 1 < n; i++) {
            auto [ux, uy, uz, ui] = pts[i];
            auto [vx, vy, vz, vi] = pts[i+1];
            int w = std::abs(vx - ux);
            adj[ui].emplace_back(vi, w);
            adj[vi].emplace_back(ui, w);
        }
    }
    {
        // сортируем по Oy и проводим рёбра между соседями:
        std::stable_sort(all(pts), [](const Point &a, const Point &b){
            return a.y < b.y;
        });
        for (int i = 0; i + 1 < n; i++) {
            auto [ux, uy, uz, ui] = pts[i];
            auto [vx, vy, vz, vi] = pts[i+1];
            int w = std::abs(vy - uy);
            adj[ui].emplace_back(vi, w);
            adj[vi].emplace_back(ui, w);
        }
    }
    {
        // сортируем по Oz и проводим рёбра между соседями:
        std::stable_sort(all(pts), [](const Point &a, const Point &b){
            return a.z < b.z;
        });
        for (int i = 0; i + 1 < n; i++) {
            auto [ux, uy, uz, ui] = pts[i];
            auto [vx, vy, vz, vi] = pts[i+1];
            int w = std::abs(vz - uz);
            adj[ui].emplace_back(vi, w);
            adj[vi].emplace_back(ui, w);
        }
    }
    // строим минимальное остовное дерево:
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
    q.push({0, 0});
    std::vector<bool> used(n);
    ll answ = 0;
    while (q.size()) {
        auto [w, i] = q.top();
        q.pop();
        if (used[i])
            continue;
        answ += w;
        used[i] = 1;
        for (const auto &[j, wij] : adj[i])
            q.push({wij, j});
    }
    std::cout << answ << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    solve();
}
