#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using namespace std;
// структура данных система непересекающихся множеств с ранговой
// эвристикой и эвристикой сжатия путей
struct DSU {
    vector<int> par, sz;
    DSU(int n) : par(n), sz(n, 1)
    {
        for (int i = 0; i < n; i++)
            par[i] = i;
    }
    int getPar(int u) {
        return par[u] == u ? u : par[u] = getPar(par[u]);
    }
    void connect(int u, int v) {
        u = getPar(u), v = getPar(v);
        if (u == v)
            return;
        if (sz[u] < sz[v])
            swap(u, v);
        sz[u] += sz[v];
        par[v] = u;
    }
};
void solve() {
    // всего может быть не больше 26 компонент - по одной
    // на каждую букву
    // один ключ объединяет в компоненту все буквы, которые содержит
    int n; cin >> n;
    DSU dsu(26);
    vector<bool> used(26);
    for (int i = 1; i <= n; i++) {
        // читаем строку
        string s; cin >> s;
        // сортируем элементы и удаляем повторы
        sort(all(s));
        s.erase(unique(all(s)), s.end());
        // отмечаем какие буквы вообще были использованы в данном тесте
        for (char c : s)
            used[c-'a'] = 1;
        // соединяем соседние буквы ключа
        for (int j = 1; j < isz(s); j++)
            dsu.connect(s[j-1]-'a', s[j]-'a');
    }
    // выводим ответ, получая количество различных компонент связности
    set<int> parents;
    for (int i = 0; i < 26; i++)
        if (used[i])
            parents.insert(dsu.getPar(i));
    cout << isz(parents) << endl;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt = 1; //cin >> tt;
    while (tt --> 0)
        solve();
}
