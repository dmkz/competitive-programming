#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем таблицу:
    int n;
    cin >> n;
    vector<string> a(n);
    for (int r = 0; r < n; r++)
        cin >> a[r];
    // переберём точки. для каждой выполним повороты
    // посмотрим, чего больше: нулей или единиц
    // того, чего меньше, прибавим к ответу
    // каждую штуку посчитаем по 4 раза, поэтому ответ поделим на 4
    int answ = 0;
    for (int row = 0; row < n; row++)
        for (int col = 0; col < n; col++)
        {
            // реализуем поворот вправо на 90 градусов:
            /*
                A -> B -> C -> D -> A:
                
                ...B.
                A....
                .....
                ....C
                .D...
                
                столбец становится строкой всегда
                новый столбец это (кол-во строк минус номер строки минус 1)
            */
            int countCells = 0, countZeros = 0;
            int currRow = row, currCol = col;
            do {
                // считаем
                countCells++;
                countZeros += (a[currRow][currCol] == '0');
                // поворачиваем
                int nextRow = currCol;
                int nextCol = n-currRow-1;
                currRow = nextRow;
                currCol = nextCol;
                // проверяем, что не прошли полный круг:
            } while (!(currRow == row && currCol == col));
            // прибавляем минимум к ответу
            int countOnes = countCells - countZeros;
            answ += min(countOnes, countZeros);
        }
    // выводим ответ
    cout << answ/4 << "\n";
}
int main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
