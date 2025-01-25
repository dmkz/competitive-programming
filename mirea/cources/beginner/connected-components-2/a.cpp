#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n; cin >> n;
    n *= 2;
    string s; cin >> s;
    map<int, int> lastPosOpened;
    vector adj(n, vector<int>{});
    int balance = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == ')') {
            // соединяем с ближайшей слева открытой скобкой,
            // обладающей таким же балансом
            balance--;
            int j = lastPosOpened[balance];
            adj[i].push_back(j);
            adj[j].push_back(i);
        } else {
            // открывающая скобка
            lastPosOpened[balance] = i;
            balance++;
        }
    }
    // соединяем соседей (i-1)<-->i, если s[i-1] == ')' и s[i] == '('
    for (int i = 1; i < n; i++)
        if (s[i] == '(' && s[i-1] == ')') {
            adj[i].push_back(i-1);
            adj[i-1].push_back(i);
        }
    // находим компоненты связности
    vector<bool> used(n); // будем отмечать уже посещённые вершины
    // рекурсивная функция, реализующая обход графа в глубину:
    function<void(int)> dfs = [&](int i) {
        if (used[i])
            return;
        used[i] = 1;
        for (int j : adj[i])
            dfs(j);
    };
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (!used[i]) { // нашли новую компоненту
            cnt++;
            dfs(i);
        }
    cout << cnt << endl;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0)
        solve();
}
