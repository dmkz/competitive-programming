#include <bits/stdc++.h>
using namespace std;
const int INF = (int)1e9;
int main() {
    // читаем все исходные данные:
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m,k; cin >> n >> m >> k;
    vector<string> field(1+n+1,string(1+m+1,'#'));
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= m; c++) {
            cin >> field[r][c];
        }
    }
    int startRow,startCol,finishRow,finishCol;
    cin >> startRow >> startCol >> finishRow >> finishCol;
    // будем хранить непосещённые клетки в n+m сетах
    // в n сетах хранятся индексы непосещенных столбцов для каждой строки
    // в m сетах хранятся индексы непосещенных строк для каждого столбца
    // это позволить за log(n) итерироваться вверх-вниз-влево-вправо на расстояние k
    // по только непосещённым клеткам и сразу их посещать
    // так как каждую клетку посещаем ровно один раз, то итоговая асимптотика O(n*m*log(n+m))
    vector<set<int>> colsForRow(1+n+1), rowsForCol(1+m+1);
    vector<vector<int>> dist(1+n+1,vector<int>(1+m+1,INF));
    for (int r = 0; r <= n+1; r++) {
        for (int c = 0; c <= m+1; c++) {
            colsForRow[r].insert(c);
            rowsForCol[c].insert(r);
        }
    }
    queue<pair<int,int>> q;
    // функция добавления клетки в очередь:
    auto push = [&](int row, int col, int currDist) {
        // добавляем клетку в очередь:
        q.push({row,col});
        // обновляем расстояние:
        dist[row][col] = currDist;
        // вырезаем из сетов непосещённых клеток:
        colsForRow[row].erase(col);
        rowsForCol[col].erase(row);
    };
    push(startRow,startCol,0); // добавляем стартовую клетку в очередь
    while (q.size()) {
        // вынимаем текущую клетку:
        auto [row,col] = q.front();
        q.pop();
        { // можем пробежать k вправо:
            auto it = colsForRow[row].lower_bound(col);
            while (*it - col <= k && field[row][*it] != '#') {
                auto next_it = next(it);
                push(row,*it,dist[row][col]+1);
                it = next_it;
            }
        }
        { // можем пробежать k влево:
            auto it = prev(colsForRow[row].upper_bound(col));
            while (col - *it <= k && field[row][*it] != '#') {
                auto prev_it = prev(it);
                push(row,*it,dist[row][col]+1);
                it = prev_it;
            }
        }
        { // можем пробежать k вниз:
            auto it = rowsForCol[col].lower_bound(row);
            while (*it - row <= k && field[*it][col] != '#') {
                auto next_it = next(it);
                push(*it,col,dist[row][col]+1);
                it = next_it;
            }
        }
        { // можем пробежать k вверх:
            auto it = prev(rowsForCol[col].upper_bound(row));
            while (row - *it <= k && field[*it][col] != '#') {
                auto prev_it = prev(it);
                push(*it,col,dist[row][col]+1);
                it = prev_it;
            }
        }
    }
    // выводим ответ:
    int answ = dist[finishRow][finishCol];
    if (answ == INF) answ = -1;
    cout << answ << endl;
}