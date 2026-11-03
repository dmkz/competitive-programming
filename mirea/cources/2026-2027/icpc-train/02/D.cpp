#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
// решение задачи:
void solve() {
    int n, m, p; cin >> n >> m >> p;
    vector a(n, string{});
    for (auto &it : a) cin >> it;
    // найдём старт и финиш
    int sr=-1,sc=-1,fr=-1,fc=-1;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++) {
            if (a[r][c] == 'S') sr = r, sc = c, a[r][c] = '.';
            if (a[r][c] == 'T') fr = r, fc = c, a[r][c] = '.';
        }
    assert(sr != -1 && sc != -1);
    assert(fr != -1 && sc != -1);
    // теперь запустим поиск в ширину. чтобы проверять возможность перемещаться в двери, храним
    // также остаток от деления количества шагов на p в состоянии вершины
    // dist[r][c][rem] = кратчайшее время, за которое мы можем попасть в клетку (r, c) с остатком rem
    const int inf = (int)1e9+1;
    vector dist(n, vector(m, vector(p, inf)));
    queue<tuple<int,int,int,int>> q;
    q.push({sr,sc,0,0});
    while (q.size()) {
        auto [r,c,rem,len] = q.front();
        q.pop();
        if (dist[r][c][rem] <= len)
            continue;
        // можем ли мы тут оказаться?
        if (a[r][c] == char('0' + rem))
            continue;
        dist[r][c][rem] = len;
        for (int dr = -1; dr <= 1; dr++)
            for (int dc = -1; dc <= 1; dc++) {
                if (dr * dr + dc * dc <= 1) { // вариант dr=0 && dc=0 соответствует ожиданию на месте
                    int nr = r + dr, nc = c + dc;
                    if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
                    if (a[nr][nc] != '#')
                        q.push({nr,nc,(rem+1)%p,len+1});
                }
            }
    }
    // находим и выводим ответ:
    int answ = inf;
    for (int rem = 0; rem < p; rem++)
        answ = min(answ, dist[fr][fc][rem]);
    if (answ >= inf)
        answ = -1;
    cout << answ << '\n';
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int tt = 1; //cin >> tt;
    while (tt --> 0) solve();
    return 0;
}
