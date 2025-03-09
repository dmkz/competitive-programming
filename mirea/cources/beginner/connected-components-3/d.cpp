#include <iostream>
#include <vector>
#include <algorithm>
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
        if (u == par[u]) return u;
        return par[u] = getPar(par[u]); // Сжатие пути
    }

    void connect(int u, int v) {
        u = getPar(u);
        v = getPar(v);
        if (u != v) {
            if (sz[u] < sz[v]) swap(u, v);
            sz[u] += sz[v];
            par[v] = u;
        }
    }
};

int main() {
    // Ускорение ввода-вывода
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    DSU dsu(n);
    
    int numFriendPairs;
    cin >> numFriendPairs;
    for (int i = 0; i < numFriendPairs; i++) {
        int u, v;
        cin >> u >> v;
        dsu.connect(u - 1, v - 1);
    }
    
    // Отмечаем, какие компоненты вообще есть
    vector<bool> canUseComp(n, false);
    for (int i = 0; i < n; i++) {
        canUseComp[dsu.getPar(i)] = true;
    }
    
    // Баним компоненты, в которых есть хейтеры
    int numHaters;
    cin >> numHaters;
    for (int i = 0; i < numHaters; i++) {
        int u, v;
        cin >> u >> v;
        u = dsu.getPar(u - 1);
        v = dsu.getPar(v - 1);
        if (u == v) {
            canUseComp[u] = false;
        }
    }
    
    // Находим ответ: максимальный размер компоненты среди оставшихся
    int answ = 0;
    for (int i = 0; i < n; i++) {
        if (canUseComp[i]) {
            answ = max(answ, dsu.sz[i]);
        }
    }
    
    cout << answ << "\n";
    return 0;
}
