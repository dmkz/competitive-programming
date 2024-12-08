#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
    // читаем данные:
    int nRows, nCols;
    cin >> nRows >> nCols;
    // находить минимальное расстоние от всех деревьев до каждой точки
    // в поиске в ширину
    vector dist(nRows, vector(nCols, INT_MAX));
    queue<pair<int,int>> q;
    // читаем деревья и заносим их в очередь:
    int nTrees; cin >> nTrees;
    for (int i = 0; i < nTrees; i++) {
        int r, c; cin >> r >> c;
        r--, c--;
        dist[r][c] = 0;
        q.push({r, c});
    }
    // поиск в ширину:
    while (q.size()) {
        auto [r, c] = q.front();
        q.pop();
        for (int dr = -1; dr <= 1; dr++)
            for (int dc = -1; dc <= 1; dc++)
                if (dr * dr + dc * dc == 1) {
                    int nr = r + dr, nc = c + dc;
                    if (nr < 0 || nr >= nRows)
                        continue;
                    if (nc < 0 || nc >= nCols)
                        continue;
                    if (dist[r][c] + 1 >= dist[nr][nc])
                        continue;
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
    }
    // найти самую удалённую точку:
    auto best = make_tuple(INT_MIN, 0, 0);
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            best = max(best, make_tuple(dist[r][c], r+1, c+1));
    // выводим ответ:
    auto [_, r, c] = best;
    cout << r << ' ' << c << endl;
}
