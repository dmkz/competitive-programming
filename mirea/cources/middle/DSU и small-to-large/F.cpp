#include <bits/stdc++.h>
using namespace std;
struct DSU {
    // для каждой компоненты связности будем хранить количество ладей в них и количество диагональных клеток
    // ладьи стремятся занять все диагональные клетки
    // если ладей < диагональных клеток, то они могут это сделать без проблем:
    // каждая ладья сделает ровно один ход
    // если количество ладей == диагональных клеток, то одной ладье придётся уступить: сделать
    // один ход в начале и один ход в конце
    
    vector<int> parent, sz, rokes, diagonals;
    
    DSU(int n) : parent(n+1), sz(n+1,1), rokes(n+1), diagonals(n+1)
    {
        for (int i = 1; i <= n; i++) parent[i] = i;
    }
    
    int getParent(int u) {
        return u == parent[u] ? u : parent[u] = getParent(parent[u]);
    }
    
    void connect(int u, int v) {
        u = getParent(u), v = getParent(v);
        if (u == v) return;
        if (sz[u] < sz[v]) swap(u,v);
        sz[u] += sz[v];
        rokes[u] += rokes[v];
        diagonals[u] += diagonals[v];
        parent[v] = u;
    }
    
    void setRoke(int u) {
        rokes[getParent(u)]++;
    }
    
    void setDiagonal(int u) {
        diagonals[getParent(u)]++;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        int n,m; cin >> n >> m;
        DSU dsu(n+m);
        // вершины с индексами от 1 до n будут соответствовать диагональным клеткам
        for (int i = 1; i <= n; i++) {
            dsu.setDiagonal(i);
        }
        // вершины с индексами от n+1 до n+m будут соответствовать ладьям
        for (int i = 1; i <= m; i++) {
            int x, y; cin >> x >> y;
            // если ладья уже в диагональной клетке, то скипаем
            // такая компонента состоит ровно из одной клетки, так как по условию
            // ладьи не бьют друг друга
            if (x == y) continue; 
            // иначе ставим ладью на поле и:
            dsu.setRoke(n+i);
            dsu.connect(n+i, x); // соединяем ладью с диагональной клеткой (x,x)
            dsu.connect(n+i, y); // соединяем ладью с диагональной клеткой (y,y)
        }
        // Надо пробежать все компоненты связностей один раз. Для этого сложим
        // представителей в set и удалим повторы
        set<int> components;
        for (int u = 1; u <= n+m; u++) {
            components.insert(dsu.getParent(u));
        }
        // Теперь для каждой компоненты считаем ответ:
        int answer = 0;
        for (int u : components) {
            int rokes = dsu.rokes[u];
            int diagonals = dsu.diagonals[u];
            if (rokes == 0) continue;
            else if (rokes == diagonals) answer += rokes+1;
            else if (rokes < diagonals) answer += rokes;
        }
        cout << answer << endl;
    }
}