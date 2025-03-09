#include <iostream>
#include <vector>
using namespace std;

// Структура для системы непересекающихся множеств
class DSU {
public:
    vector<int> sz, par, numEdges;

    DSU(int n) {
        sz.resize(n, 1);
        par.resize(n);
        numEdges.resize(n, 0);
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
            numEdges[u] += numEdges[v];
        }
        numEdges[u] += 1;
    }
};

int main() {
    // Ускорение ввода-вывода
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int nVert, nEdges;
    cin >> nVert >> nEdges;
    DSU dsu(nVert);
    
    for (int i = 0; i < nEdges; i++) {
        int u, v;
        cin >> u >> v;
        dsu.connect(u - 1, v - 1);
    }
    
    // Отмечаем, какие вершины являются представителями компонент связностей
    vector<bool> isParent(nVert, false);
    for (int i = 0; i < nVert; i++) {
        isParent[dsu.getPar(i)] = true;
    }
    
    // Подсчет количества деревьев
    int answ = 0;
    for (int p = 0; p < nVert; p++) {
        if (isParent[p]) {
            answ += max(0, dsu.sz[p] - dsu.numEdges[p]);
        }
    }
    
    cout << answ << "\n";
    return 0;
}
