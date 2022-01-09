#include <bits/stdc++.h>
using namespace std;

struct DSU {
    // dsu именно для башен и их номеров, то есть вершина - башня
    vector<int> parent, sz, t; // t[диск] -> номер башни, в которой лежит
    vector<vector<int>> items; // items[башня] -> все элементы, лежащие в башне
    int answ{0};
    
    DSU(int n) : parent(n+1), sz(n+1), t(n), items(n+1)
    {
        for (int u = 1; u <= n; u++) {
            parent[u] = u;
        }
    }
    
    void calcAnswer() {
        // ответ на задачу это "количество отрезков из равных элементов в массиве t" - 1
        // то есть ответ равен (t[1] != t[2]) + (t[2] != t[3]) + ... + (t[n-1] != t[n])
        answ = 0;
        for (int i = 1; i < (int)t.size(); i++) {
            answ += (t[i-1] != t[i]);
        }
    }
    
    int getParent(int u) {
        return parent[u] == u ? u : parent[u] = getParent(parent[u]);
    }
    
    void connect(int u, int v) {
        u = getParent(u), v = getParent(v);
        if (u == v) return;
        if (sz[u] < sz[v]) swap(u,v);
        // нам нужно аккуратно пересчитать ответ вида
        // (t[1] != t[2]) + (t[2] != t[3]) + ... + (t[n-1] != t[n])
        // мы меняем сумму, вычитая те слагаемые, которые уже были, и прибавляя новые
        // заодно перекладываем из меньшей башни в большую
        for (auto disk : items[v]) {
            // смотрим соседей и вычитаем из ответа уже существующие различия:
            if (disk - 1 >= 0 && t[disk-1] != t[disk]) answ--;
            if (disk + 1 < (int)t.size() && t[disk+1] != t[disk]) answ--;
            // присваиваем новую башню для диска:
            t[disk] = u;
            items[u].push_back(disk);
            // прибавляем к ответу новые различия:
            if (disk - 1 >= 0 && t[disk-1] != t[disk]) answ++;
            if (disk + 1 < (int)t.size() && t[disk+1] != t[disk]) answ++;
        }
        parent[v] = u;
        sz[u] += sz[v];
    }
    
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    DSU dsu(n);
    for (int i = 0; i < n; i++) {
        // апдейтим dsu для диска i и башни t:
        int t; cin >> t;
        dsu.t[i] = t;
        dsu.items[t].push_back(i);
        dsu.sz[t]++;
    }
    dsu.calcAnswer();
    for (int i = 0; i < q; i++) {
        cout << dsu.answ << "\n";
        int u, v; cin >> u >> v;
        dsu.connect(u,v);
    }
}