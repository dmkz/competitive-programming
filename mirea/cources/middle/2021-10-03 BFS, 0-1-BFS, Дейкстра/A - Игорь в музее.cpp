#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем исходное поле:
    int n,m,k; cin >> n >> m >> k;
    vector<string> a(n,string(m,'.'));
    for (auto &row : a) cin >> row;
    // нужно, запуская bfs из непосещённых клеток, найти компоненты связности
    // и количество рёбер, упирающихся в стену в каждой компоненте
    
    vector<vector<int>> idComponent(n,vector<int>(m));
    vector<int> answ(n*m+1); // answ[i] - ответ для компоненты под номером i
    
    // функция для алгоритма bfs:
    auto bfs = [&](int row, int col, int comp) {
        queue<pair<int,int>> q;
        q.push({row,col});
        while (!q.empty()) {
            // вынимаем вершину из очереди:
            auto [r,c] = q.front();
            q.pop();
            // если она стена, то прибавляем к ответу 1:
            if (a[r][c] == '*') {
                answ[comp]++;
                continue;
            }
            // иначе это пустая клетка. если ещё не посещена, то посещаем
            if (idComponent[r][c]) continue;
            idComponent[r][c] = comp;
            // и добавляем всех соседей в очередь:
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
    // после того, как всё посчитали, начинаем отвечать на запросы:
    while (k --> 0) {
        int r, c; cin >> r >> c;
        r--,c--;
        int comp = idComponent[r][c];
        cout << answ[comp] << '\n';
    }
    return 0;
}