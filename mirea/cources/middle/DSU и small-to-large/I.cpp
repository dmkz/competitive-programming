#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    // читаем все данные, которые нужны:
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<int> color(1+n);
    vector<vector<int>> adj(1+n);
    for (int u = 1; u <= n; u++) cin >> color[u];
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // будем решать задачу. Для каждого поддерева нужно хранить
    // map[цвет] = его количество
    // max[вершина] = максимальное количество одного цвета в поддереве
    // sum[вершина] = сумма максимальных цветов в поддереве
    vector<int> max(1+n);
    vector<ll> sum(1+n);
    vector<map<int,int>*> cnt(1+n);
    auto addToMap = [&](int u, int col, int count) {
        // функция добавления цвета `col` в количестве `count` в
        // мапу для вершины `u`.
        (*cnt[u])[col] += count; // инкрементим количество
        if (max[u] < (*cnt[u])[col]) {
            // если мы достигли нового максимума, то сумма
            // становится равной одному этому цвету
            sum[u] = col;
            max[u] = (*cnt[u])[col];
            return;
        }
        if (max[u] == (*cnt[u])[col]) {
            // если мы сравнялись с предыдущим максимумом, то
            // сумма увеличивается на этот цвет
            sum[u] += col;
        }
    };
    function<void(int,int)> dfs = [&](int u, int p) {
        // запускаем dfs для всех поддеревьев
        bool isLeaf = true;
        for (int v : adj[u]) {
            if (v == p) continue;
            isLeaf = false;
            dfs(v, u);
        }
        // если лист, то всё очевидно, так как цвет ровно один:
        if (isLeaf) {
            cnt[u] = new map<int,int>{{color[u],1}};
            sum[u] = color[u];
            max[u] = 1;
            return;
        }
        // теперь нужно выбрать мапу с максимальным размером
        // среди сыновей и всё туда перекинуть по эвристике 
        // small-to-large.
        int maxSize = 0;
        for (int v : adj[u]) {
            if (v == p) continue;
            if (cnt[v]->size() > maxSize) {
                maxSize = cnt[v]->size();
                cnt[u] = cnt[v];
                sum[u] = sum[v];
                max[u] = max[v];
            }
        }
        // максимальную мапу выбрали, осталось туда всё перекинуть:
        addToMap(u, color[u], 1);
        for (int v : adj[u]) {
            if (v == p || cnt[v] == cnt[u]) continue;
            for (auto &[col, count] : *cnt[v]) {
                addToMap(u, col, count);
            }
            delete cnt[v];
        }
    };
    // запускаем dfs из корня дерева:
    dfs(1,0);
    delete cnt[1];
    for (int u = 1; u <= n; u++) {
        cout << sum[u] << ' ';
    }
    
}