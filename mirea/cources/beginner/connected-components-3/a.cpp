#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// структура для системы неперекающихся множеств
class DSU {
public:
    vector<int> sz, par;

    DSU(int n) {
        sz.resize(n, 1);
        par.resize(n);
        for (int i = 0; i < n; i++) {
            par[i] = i;
        }
    }

    int getPar(int u) {
        if (u == par[u]) return u;
        return par[u] = getPar(par[u]);
    }

    void connect(int u, int v) {
        u = getPar(u);
        v = getPar(v);
        if (u != v) {
            if (sz[u] < sz[v]) swap(u, v); // swap
            sz[u] += sz[v];
            par[v] = u;
        }
    }
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    DSU dsu(n);

    // пробегаемся по всем подстрокам длины k и проводим рёбра
    // между позициями символов, которые должны быть равны
    for (int start = 0; start <= n - k; start++) {
        for (int i = 0; i < k / 2; i++) {
            dsu.connect(start + i, start + k - 1 - i);
        }
    }

    // теперь считаем количество различных компонент
    vector<int> parents;
    for (int i = 0; i < n; i++) {
        parents.push_back(dsu.getPar(i));
    }
    sort(parents.begin(), parents.end());
    parents.erase(unique(parents.begin(), parents.end()), parents.end());

    // выводим ответ: для каждой компоненты можем выбрать один из m символов
    // произвольно, поэтому ответ равен m в степени количества компонент:
    const int MOD = 1000000007;
    long long result = 1;
    for (int i = 0; i < parents.size(); i++) {
        result = (result * m) % MOD;
    }
    cout << result << endl;
    return 0;
}