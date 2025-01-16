#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем входные данные
    int nRows, nCols, nQueries;
    cin >> nRows >> nCols >> nQueries;
    // читаем поле из символов
    vector<string> a(nRows);
    for (auto &it : a)
        cin >> it;
    // нужно найти компоненты связности (комнаты) и запомнить их номера
    // для каждой пустой клетки поля. Ответом на запрос для комнаты
    // является количество раз, которое мы упёрлись в стенку во время
    // обхода в ширину или обхода в глубину
    int numComponents = 0;
    vector<int> answerForComponent = {0};
    vector component(nRows, vector(nCols, 0));
    for (int sr = 0; sr < nRows; sr++)
        for (int sc = 0; sc < nCols; sc++)
            if (a[sr][sc] == '.' && !component[sr][sc]) {
                numComponents++;
                component[sr][sc] = numComponents;
                queue<pair<int,int>> q;
                q.push({sr,sc});
                int numWalls = 0;
                while (!q.empty()) {
                    // вынимаем текущую вершину из очереди
                    auto [r, c] = q.front();
                    q.pop();
                    // посещаем всех соседей:
                    // переберём все векторы перемещения и будем шагать
                    // по тем, которые переходят в соседнюю по стороне клетку
                    for (int dr = -1; dr <= 1; dr++)
                        for (int dc = -1; dc <= 1; dc++) {
                            if (dr * dr + dc * dc != 1)
                                continue;
                            int nr = r + dr, nc = c + dc;
                            if (a[nr][nc] == '*') { // видим стену
                                numWalls++;
                            } else if (!component[nr][nc]) {
                                // видим пустую непосещённую клетку
                                // добавляем её в очередь
                                component[nr][nc] = numComponents;
                                q.push({nr, nc});
                            }
                        }
                }
                answerForComponent.push_back(numWalls);
            }
    // читаем запросы и отвечаем на них
    while (nQueries --> 0) {
        int row, col; cin >> row >> col;
        row--, col--;
        // находим номер компоненты и берём ответ для неё
        int compId = component[row][col];
        cout << answerForComponent[compId] << '\n';
    }
}
