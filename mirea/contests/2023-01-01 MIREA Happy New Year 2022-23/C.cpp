#include <bits/stdc++.h>
using namespace std;
using ll = long long;
auto getPath(ll u) {
// используем тот факт, что у вершины p сыновья это 6*p-4, 6*p-3, 6*p-2, 6*p-1, 6*p и 6*p+1
// значит, зная u, чтобы найти p, нужно прибавить 4 и поделить на 6 с округлением вниз
    vector<ll> path{u};
    while (u != 1) {
        u = (u + 4) / 6;
        path.push_back(u);
    }
    return path;
}
int dist(ll u, ll v) {
// находим расстояние между u и v
// сперва надо найти путь до корня для обеих вершин
// затем удалить общую часть пути
    auto path_u = getPath(u);
    auto path_v = getPath(v);
// удаляем общую часть пути:
    while (!path_u.empty() && !path_v.empty() && path_u.back() == path_v.back()) {
        path_u.pop_back();
        path_v.pop_back();
    }
// ответ - сумма оставшихся размеров пути
    return int(path_u.size() + path_v.size());
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt--) {
        ll u, v; cin >> u >> v;
        cout << dist(u,v) << '\n';
    }
}