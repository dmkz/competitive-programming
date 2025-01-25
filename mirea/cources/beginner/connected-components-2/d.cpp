#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
void solve() {
    int n; cin >> n;
    string s, t;
    cin >> s >> t;
    // если s[i] != t[i], то мы должны иметь путь в графе букв между s[i] и t[i]
    // найдём компоненты связности. Оптимальнее будет построить дерево
    // в каждой компоненте и купить рёбра дерева (k-1) заклинаний, если
    // в компоненте k элементов
    vector adj(26, vector<int>{});
    vector<bool> used(26);
    for (int i = 0; i < n; i++)
        if (s[i] != t[i]) {
            int u = s[i]-'a', v = t[i] - 'a';
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    // ищем размер каждой компоненты в графе
    // так как нужно выводить сами заклинания, то нам потребуются все
    // буквы, лежащие в одной компоненте, и соединяем их
    vector<pair<char,char>> rules;
    for (int p = 0; p < n; p++)
        if (int u = s[p] - 'a'; s[p] != t[p] && !used[u]) {
            // ищем компоненту связности
            vector<int> items;
            // функция, реализующая обход графа в глубину:
            function<void(int)> dfs = [&](int v) {
                if (used[v])
                    return;
                used[v] = 1;
                items.push_back(v);
                for (int next : adj[v])
                    dfs(next);
            };
            // запускаем dfs из вершины u (буквы, стоящей на позиции i)
            dfs(u);
            // обновляем ответ:
            for (int i = 0; i + 1 < isz(items); i++)
                rules.emplace_back('a' + items[i], 'a' + items[i+1]);
        }
    // выводим ответ:
    cout << isz(rules) << '\n';
    for (const auto &[fi, se] : rules)
        cout << fi << ' ' << se << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt = 1; //cin >> tt;
    while (tt --> 0)
        solve();
}

