#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Структура для системы непересекающихся множеств
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
        if (u == par[u]) {
            return u;
        }
        return par[u] = getPar(par[u]); // сжатие пути
    }

    void connect(int u, int v) {
        u = getPar(u);
        v = getPar(v);
        if (u != v) {
            if (sz[u] < sz[v]) {
                swap(u, v);
            }
            sz[u] += sz[v];
            par[v] = u;
        }
    }
};

// Оставить только уникальные элементы в сортированном списке
void unique(vector<int>& s) {
    int p = 0;
    for (int i = 0; i < s.size(); ) {
        int j = i;
        while (j < s.size() && s[i] == s[j]) {
            j++;
        }
        s[p++] = s[i];
        i = j;
    }
    s.resize(p);
}

int main() {
    const int mod = 1e9 + 7;
    int n, k;
    cin >> n >> k;

    DSU dsu(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, x;
        cin >> u >> v >> x;
        if (x == 0) {
            dsu.connect(u - 1, v - 1);
        }
    }

    // Найти размеры компонент
    vector<int> parents;
    for (int i = 0; i < n; i++) {
        parents.push_back(dsu.getPar(i));
    }
    sort(parents.begin(), parents.end());
    unique(parents);

    // Теперь считаем ответ: n^k минус сумма sz[p]^k по каждой компоненте
    long long answ = 1;
    for (int i = 0; i < k; i++) {
        answ = (answ * n) % mod;
    }
    
    for (int p : parents) {
        long long sub = 1;
        for (int i = 0; i < k; i++) {
            sub = (sub * dsu.sz[p]) % mod;
        }
        answ = (answ - sub + mod) % mod;
    }
    
    cout << answ << endl;
    return 0;
}