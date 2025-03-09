#include <iostream>
#include <vector>
using namespace std;

// Структура для системы непересекающихся множеств
class DSU {
public:
    vector<int> sz, par;
    int numComponents;

    DSU(int n) : numComponents(n) {
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
            numComponents--;
        }
    }
};

int main() {
    // Ускорение ввода-вывода
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
        }

        DSU dsu(n);
        for (int i = 0; i < n; i++) {
            dsu.connect(i, a[i]);
        }

        // Подсчет минимального ответа
        vector<int> uniqEdges(n, 0);
        vector<bool> isParent(n, false);
        for (int i = 0; i < n; i++) {
            int pi = dsu.getPar(i);
            uniqEdges[pi] = 2 * dsu.sz[pi];
            isParent[pi] = true;
        }

        // Вычитание петель
        for (int u = 0; u < n; u++) {
            if (a[a[u]] == u) {
                uniqEdges[dsu.getPar(u)]--;
            }
        }

        // Подсчет количества циклов и деревьев
        int nCycles = 0, nTrees = 0;
        for (int i = 0; i < n; i++) {
            if (isParent[i]) {
                if (uniqEdges[i] == 2 * dsu.sz[i]) {
                    nCycles++;
                } else {
                    nTrees++;
                }
            }
        }

        int minAnsw = nCycles + (nTrees > 0 ? 1 : 0);
        int maxAnsw = dsu.numComponents;
        cout << minAnsw << " " << maxAnsw << "\n";
    }
    return 0;
}