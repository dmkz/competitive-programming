#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем исходное поле:
    int n,m; cin >> n >> m;
    vector<string> a(n,string(m,'.'));
    for (auto &row : a) cin >> row;
    // нужно, запуская bfs из непосещённых клеток, найти компоненты связности
    // и количество вершин в этих компонентах
    
    vector<vector<int>> idComponent(n,vector<int>(m));
    vector<int> answ(n*m+1); // answ[i] - количество вершин в компоненте i
    
    // функция для алгоритма bfs:
    auto bfs = [&](int row, int col, int comp) {
        queue<pair<int,int>> q;
        q.push({row,col});
        while (!q.empty()) {
            // вынимаем вершину из очереди:
            auto [r,c] = q.front();
            q.pop();
            // ничего не делаем, если вышли за пределы поля:
            if (r < 0 || r >= n || c < 0 || c >= m) continue;
            // ничего не делаем для стены:
            if (a[r][c] == '*') continue;
            // ничего не делаем для уже посещённой клетки:
            if (idComponent[r][c]) continue;
            // только теперь начинаем обрабатывать вершину
            idComponent[r][c] = comp;
            answ[comp]++;
            // добавляем всех соседей данной вершины в очередь:
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    // можем перемещаться только в соседние по стороне клетки
                    if (dr * dr + dc * dc != 1) continue;
                    q.push({r+dr,c+dc});
                }
            }
        }
    };
    // запускаем bfs из каждой непосещённой вершины:
    int nComp = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (a[row][col] == '.' && !idComponent[row][col]) {
                // запускаем bfs
                bfs(row,col,++nComp);
            }
        }
    }
    // теперь всё, что нужно, посчитано, начинаем формировать ответ
    vector<string> out(n,string(m,'.'));
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (a[r][c] == '*') {
                // берём компоненты у соседних пустых вершин:
                set<int> s;
                for (int dr = -1; dr <= 1; dr++) {
                    for (int dc = -1; dc <= 1; dc++) {
                        if (dr * dr + dc * dc != 1) continue;
                        int nr = r + dr, nc = c + dc;
                        if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
                        if (a[nr][nc] == '*') continue;
                        s.insert(idComponent[nr][nc]);
                    }
                }
                int total = 1;
                for (auto it : s) total += answ[it];
                out[r][c] = char('0' + total % 10);
            }
        }
        cout << out[r] << '\n';
    }
    return 0;
}