#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем число строк и столбцов:
    int nRows, nCols;
    cin >> nRows >> nCols;
    // читаем поле, находим начальное и конечное положения:
    int startRow, startCol, finishRow, finishCol;
    vector<vector<char>> field(nRows,vector<char>(nCols));
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nCols; col++) {
            cin >> field[row][col];
            // это стартовая клетка?
            if (field[row][col] == 'S') {
                startRow = row, startCol = col;
                field[row][col] = '.';
            }
            // это финишная клетка?
            if (field[row][col] == 'T') {
                finishRow = row, finishCol = col;
                field[row][col] = '.';
            }
        }
    }
    // запускаем 0-1-bfs
    const int INF = (int)1e9;
    using vi = vector<int>;   // тип вектора целых чисел
    using vvi = vector<vi>;   // тип вектора векторов целых чисел
    using vvvi = vector<vvi>; // тип вектора вектора векторов целых чисел
    // вершины графа - тройки (направление, строка, столбец)
    // изначальное расстояние равно бесконечности
    vvvi dist(4,vvi(nRows,vi(nCols,INF)));
    // заносим в двунаправленную очередь стартовое положения для всех 4 направлений:
    deque<tuple<int,int,int,int>> q;
    for (int dir = 0; dir < 4; dir++) {
        q.push_front({dir,startRow,startCol,0});
    }
    // ВЛЕВО-0 ВВЕРХ-1 ВПРАВО-2 ВНИЗ-3
    const int drow[] = { 0,-1, 0,+1};
    const int dcol[] = {-1, 0,+1, 0};
    while (!q.empty()) {
        // вынимаем текущую вершину
        auto [dir,row,col,distance] = q.front();
        q.pop_front();
        // делаем все необходимые проверки и пропускаем если нужно
        if (row < 0 || row >= nRows) continue;
        if (col < 0 || col >= nCols) continue;
        if (field[row][col] == '*') continue;
        if (dist[dir][row][col] <= distance) continue;
        // обновляем расстояние до текущей вершины:
        dist[dir][row][col] = distance;
        // ребра веса ноль - переход вперёд в текущем направлении dir
        q.push_front({dir,row+drow[dir],col+dcol[dir],distance});
        // ребра веса один - поворот в соседние направления
        q.push_back({(dir+1)%4,row,col,distance+1});
        q.push_back({(dir+3)%4,row,col,distance+1});
    }
    // 0-1-bfs завершился, находим минимум до финишной точки для всех четырех направлений:
    int minDist = INF;
    for (int dir = 0; dir < 4; dir++) {
        minDist = min(minDist,dist[dir][finishRow][finishCol]);
    }
    // и выводим ответ:
    if (minDist > 2) cout << "NO\n";
    else cout << "YES\n";
}