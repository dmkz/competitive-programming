#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;

void solve() {
    // читаем:
    int n; int64_t k;
    cin >> n >> k;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }
    // ищем циклы + находим ответ:
    vector<int> answer(n);
    vector<int> cycle;
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            // в цикле должны посетить все вершины и вернуться в i
            // ищем цикл:
            cycle = {i};
            for (int j = p[i]; j != i; j = p[j])
                cycle.push_back(j);
            // находим ответ:
            for (int j = 0; j < isz(cycle); j++) {
                int curr = cycle[j];
                int next = cycle[(j + k) % isz(cycle)];
                answer[curr] = next;
            }
            // отмечаем вершины цикла посещёнными:
            for (auto item : cycle)
                visited[item] = 1;
        }
    }
    // выводим ответ:
    for (int i = 0; i < n; i++)
        cout << answer[i] + 1 << ' ';
    cout << '\n';
}

main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // решение задачи
    int tt; cin >> tt;
    while (tt --> 0)
        solve();
}
