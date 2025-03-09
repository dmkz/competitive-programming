#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Быстрое возведение в степень по модулю
long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

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
    parents.erase(unique(parents.begin(), parents.end()), parents.end());

    // Теперь считаем ответ: n^k минус сумма sz[p]^k по каждой компоненте
    long long answ = modPow(n, k, mod);
    
    for (int p : parents) {
        answ = (answ - modPow(dsu.sz[p], k, mod) + mod) % mod;
    }
    
    cout << answ << endl;
    return 0;
}