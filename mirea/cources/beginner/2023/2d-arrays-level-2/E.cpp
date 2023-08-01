#include <bits/stdc++.h>
using namespace std;
int main() {
    // вместо массива 10 x 10 создаём массив 20 x 20, добавляя 5 пустых строк
    // и 5 пустых столбцов слева/справа/сверху/снизу, чтобы не выйти за границы
    vector arr(20, string(20, 'O'));
    for (int i = 5; i < 5 + 10; ++i) {
        cin >> arr[i];
        arr[i] = string(5, 'O') + arr[i] + string(5, 'O');
    }
    for (int i = 5; i < 15; ++i) {
        for (int j = 5; j < 15; ++j) {
            // переберём все 8 векторов в качестве направления
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (di == 0 && dj == 0)
                        continue;
                    // и пробежим 5 клеток в выбранном направлении,
                    // считая количество 'X' и '.' 
                    int cntX = 0, cntD = 0;
                    for (int k = 0; k < 5; ++k) {
                        cntX += (arr[i+k*di][j+k*dj] == 'X');
                        cntD += (arr[i+k*di][j+k*dj] == '.');
                    }
                    if (cntX == 4 && cntD == 1) {
                        cout << "YES\n";
                        return 0;
                    }
                }
            }            
        }
    }
    cout << "NO\n";
    return 0;
}