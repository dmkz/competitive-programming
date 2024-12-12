#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
void part1() {
    // чтение
    string ss;
    vector<string> a;
    while (getline(cin, ss))
        a.push_back(ss);
    const int nRows = isz(a);
    const int nCols = isz(a[0]);
    // добавляем точки по границе поля:
    a.insert(a.begin(), string(nCols+2, '.'));
    a.insert(a.end(), string(nCols+2, '.'));
    for (int r = 1; r <= nRows; r++)
        a[r] = "." + a[r] + ".";
    // запускаем поиск в глубину для каждой области
    vector visited(1+nRows+1, vector(1+nCols+1, false));
    vector<int> p, s;
    int nComp{};
    function<void(int,int,int)> dfs = [&](int r, int c, int id) {
        if (visited[r][c])
            return;
        visited[r][c] = 1;
        s[id]++;
        for (int dr = -1; dr <= 1; dr++)
            for (int dc = -1; dc <= 1; dc++)
                if (dr * dr + dc * dc == 1) {
                    int nr = r + dr, nc = c + dc;
                    if (a[r][c] == a[nr][nc])
                        dfs(nr, nc, id);
                    else
                        p[id]++;
                }
    };
    int64_t answ{};
    for (int r = 1; r <= nRows; r++)
        for (int c = 1; c <= nCols; c++)
            if (!visited[r][c]) {
                // нашли новую компоненту
                nComp++;
                p.push_back(0);
                s.push_back(0);
                dfs(r, c, nComp-1);
                answ += p.back() * s.back();
                cout << a[r][c] << ": " << s.back() << " " << p.back() << endl;
            }
    cout << answ << endl;
}
struct DSU {
    vector<int> par, sz;
    DSU(int n) : par(n, -1), sz(n, 1)
    {
        for (int u = 0; u < n; u++)
            par[u] = u;
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
const int up = 0, right = 1, down = 2, left = 3;
const int dr[] = {-1, 0, +1, 0};
const int dc[] = { 0,+1, 0, -1};
void part2() {
    // чтение
    string ss;
    vector<string> a;
    while (getline(cin, ss))
        a.push_back(ss);
    const int nRows = isz(a);
    const int nCols = isz(a[0]);
    // добавляем точки по границе поля:
    a.insert(a.begin(), string(nCols+2, '.'));
    a.insert(a.end(), string(nCols+2, '.'));
    for (int r = 1; r <= nRows; r++)
        a[r] = "." + a[r] + ".";
    // запускаем поиск в глубину для каждой области
    vector visited(1+nRows+1, vector(1+nCols+1, false));
    vector<int> p, s;
    vector<set<tuple<int,int,int>>> sides;
    int nComp{};
    function<void(int,int,int)> dfs = [&](int r, int c, int id) {
        if (visited[r][c])
            return;
        visited[r][c] = 1;
        s[id]++;
        for (int dir = 0; dir < 4; dir++) {
            int nr = r + dr[dir], nc = c + dc[dir];
            if (a[r][c] == a[nr][nc])
                dfs(nr, nc, id);
            else {
                sides[id].insert({r, c, dir});
                p[id]++;
            }
        }
    };
    DSU dsu(4 * nRows * nCols);
    auto getIndex = [&](int r, int c, int dir) -> int {
        const int result = dir + 4 * ((c-1) + nCols * (r-1));
        assert(result >= 0);
        assert(result < 4 * nRows * nCols);
        return result;
    };
    int64_t answ{};
    for (int r = 1; r <= nRows; r++)
        for (int c = 1; c <= nCols; c++)
            if (!visited[r][c]) {
                // нашли новую компоненту
                nComp++;
                p.push_back(0);
                s.push_back(0);
                sides.push_back({});
                dfs(r, c, nComp-1);
                // нужно посчитать количество сторон, объединяя соседние стороны
                for (const auto &[r2, c2, dir2] : sides.back()) {
                    for (auto newDir : {(dir2-1+4)%4,(dir2+1)%4}) {
                        int nr = r2 + dr[newDir];
                        int nc = c2 + dc[newDir];
                        if (sides.back().count(make_tuple(nr, nc, dir2))) {
                            dsu.connect(getIndex(r2,c2,dir2), getIndex(nr, nc, dir2));
                        }
                    }
                }
                // считаем количество компонент в графе сторон:
                // для этого достаём всех представителей каждой из границ:
                vector<int> uniqSides;
                for (const auto &[r2, c2, dir2] : sides.back())
                    uniqSides.push_back(dsu.getPar(getIndex(r2,c2,dir2)));
                // сортируем этих представителей + удаляем повторы:
                sort(all(uniqSides));
                uniqSides.erase(unique(all(uniqSides)), uniqSides.end());
                // количество сторон:
                int nSides = isz(uniqSides);
                answ += nSides * s.back();
                cout << a[r][c] << ": " << s.back() << " " << nSides << endl;
            }
    cout << answ << endl;
}
main() {
    part2();
}

