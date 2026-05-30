#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем:
    int n; cin >> n;
    vector<pair<int,int>> edges;
    for (int i = 1; i <= n; i++) {
        int j; cin >> j;
        edges.push_back({i, j});
    }
    // разворачиваем стрелки:
    for (auto &[i, j] : edges)
        swap(i, j);
    // сортируем пары лексикографически:
    sort(edges.begin(), edges.end());
    // выводим ответ:
    for (const auto &[_, j] : edges)
        cout << j << ' ';
}