#include <bits/stdc++.h>
using namespace std;
const int INF = (int)1e9;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем исходное поле:
    int n,m,d; cin >> n >> m >> d;
    vector<string> a(n,string(m,'.'));
    for (auto &row : a) cin >> row;
    // нужно запустить bfs от всех монстров и забанить для передвижения все клетки,
    // достижимые из них за d шагов
    vector<vector<int>> dist(n,vector<int>(m,INF));
    queue<tuple<int,int,int>> q;
    int startRow,startCol,finishRow,finishCol;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (a[r][c] == 'M') {
                q.push({r,c,0});
            } else if (a[r][c] == 'S') {
                startRow = r, startCol = c;
            } else if (a[r][c] == 'F') {
                finishRow = r, finishCol = c;
            }
            a[r][c] = '.';
        }
    }
    while (!q.empty()) {
        // вынимаем текущую клетку
        auto [r,c,currDist] = q.front();
        q.pop();
        // если превысили лимит шагов, то ничего не делаем:
        if (currDist > d) continue;
        // если вышли за пределы поля или уже тут были, то ничего не делаем:
        if (r < 0 || r >= n || c < 0 || c >= m) continue;
        if (dist[r][c] <= currDist) continue;
        // иначе наконец-то посещаем клетку:
        dist[r][c] = currDist;
        a[r][c] = '#';
        // и добавляем в очередь всех её соседей:
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr * dr + dc * dc != 1) continue;
                q.push({r+dr,c+dc,currDist+1});
            }
        }
    }
    // теперь все достижимые монстрами клетки посещены
    // на их месте стоят символы #
    // можем спокойно передвигаться из S в F
    dist.assign(n,vector<int>(m,INF));
    q.push({startRow,startCol,0});
    while (!q.empty()) {
        // вынимаем текущую клетку
        auto [r,c,currDist] = q.front();
        q.pop();
        // если вышли за пределы поля или уже тут были или пришли в стену, то ничего не делаем:
        if (r < 0 || r >= n || c < 0 || c >= m) continue;
        if (dist[r][c] <= currDist || a[r][c] == '#') continue;
        // иначе посещаем клетку:
        dist[r][c] = currDist;
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr * dr + dc * dc != 1) continue;
                q.push({r+dr,c+dc,currDist+1});
            }
        }
    }
    // выводим ответ
    int answ = dist[finishRow][finishCol];
    if (answ == INF) answ = -1;
    cout << answ << endl;
    return 0;
}