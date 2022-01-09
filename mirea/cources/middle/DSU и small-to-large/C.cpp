// Будем решать через DSU за O(n^2)
// Соединяем вершины с соседями по мере выключения света
// Как только в какой-то компоненте связности появился и монстр, и граничная вершина, то
// значит, что этот монстр может убежать в эту граничную вершину - завершаем работу программы
#include <bits/stdc++.h>

using namespace std;

struct DSU {
    // нужно хранить размер поля n и для каждой компоненты количество монстров и
    // граничных клеток в ней
    const int n;
    vector<int> parent, sz, monsters, borders;
    
    // конструктор системы непересекающихся множеств
    DSU(int n_) : n(n_), parent(n*n), sz(n*n), monsters(n*n), borders(n*n)
    {
        for (int i = 0; i < n*n; i++) {
            // изначально каждое дерево состоит из одной вершины i и имеет размер 1
            parent[i] = i;
            sz[i] = 1;
        }
    }
    
    // добавление граничной клетки (r,c) в её компоненту связности:
    void addBorder(int r, int c) {
        int u = getParent(r,c);
        borders[u]++;
    }
    
    // добавление монстра (r,c) в его компоненту связности:
    void addMonster(int r, int c) {
        int u = getParent(r,c);
        monsters[u]++;
    }
    
    // проверка на то, что в компоненте связности, содержащей клетку (r,c),
    // есть хотя бы один монстр и хотя бы одна граничная клетка:
    bool check(int r, int c) {
        int u = getParent(r,c);
        return monsters[u] > 0 && borders[u] > 0;
    }
    
    // поиск корня дерева в компоненте связности клетки (r,c):
    int getParent(int r, int c) {
        return getParent(r*n+c);
    }
    
    // поиск корня дерева в компоненте связности вершины (u:
    int getParent(int u) {
        // эвристика сжатия путей:
        return u == parent[u] ? u : parent[u] = getParent(parent[u]);
    }
    
    // объединение двух компонент для вершин (r1,c1) и (r2,c2):
    void connect(int r1, int c1, int r2, int c2) {
        // сначала находим корни деревьев, соответствующих компонентам связности:
        int u = getParent(r1,c1), v = getParent(r2,c2);
        if (u == v) return; // если корни совпадают, то объединять не нужно - лежат в одной компоненте
        // эвристика размера: объединяем v к u, причём размер(u) >= размер (v)
        if (sz[u] < sz[v]) swap(u,v);
        sz[u] += sz[v]; // размеры складываются
        parent[v] = u; // проводим ребро из корня компоненты u в корень компоненты v
        monsters[u] += monsters[v]; // монстры складываются
        borders[u] += borders[v]; // граничные клетки складываются
    }
};

int main() {
    // читаем размеры поля, количество монстров и количество выключений света:
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    // создаём поле n x n. a[i][j] = '#' если свет включен, иначе '.'
    vector<string> a(n, string(n,'#'));
    DSU dsu(n); // создаём систему непересекающихся множеств на n x n вершин
    
    // функция соединения клетки (r,c) с соседями на клетчатом поле:
    auto connectWithAdjacent = [&](int r, int c)
    {
        // перебираем все соседние по стороне клетки и если там выключен свет, то соединяем
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr*dr+dc*dc != 1) continue;
                int nr = r + dr, nc = c + dc;
                if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
                if (a[nr][nc] != '.') continue;
                dsu.connect(r,c,nr,nc);
            }
        }
    };
    
    // отмечаем границы:
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (r == 0 || r == n-1 || c == 0 || c == n-1) {
                dsu.addBorder(r,c);
            }
        }
    }
    
    // отмечаем монстров:
    for (int i = 0; i < m; i++) {
        int r, c; cin >> r >> c;
        a[r][c] = '.';
        dsu.addMonster(r,c); // добавляется монстр
        connectWithAdjacent(r,c); // соединяется с соседями
        if (dsu.check(r,c)) {
            // если компонента для (r,c) уже содержит монстра и граничную клетку,
            // то выводим ответ
            cout << "0\n";
            return 0;
        }
    }
    
    // обрабаываем моменты выключения света:
    for (int t = 1; t <= k; t++) {
        int r,c; cin >> r >> c;
        a[r][c] = '.'; // выключаем свет
        connectWithAdjacent(r,c); // соединяется с соседями
        if (dsu.check(r,c)) {
            // если компонента для (r,c) содержит монстра и граничную клетку,
            // то выводим ответ
            cout << t << '\n';
            return 0;
        }
    }
    // по условию гарантируется, что спустя k точно можно сбежать
    // значит мы завершим программу точно внутри цикла for
    assert(false);
    return 0;
}