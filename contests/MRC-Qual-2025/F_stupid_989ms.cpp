// Задача: F, Вердикт: OK, Время: 0.989s, Память: 37.77Mb
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
using Pair = pair<int64_t, int>;
using Tuple = tuple<int64_t, int, int, int, int>;
const int64_t inf = 1e18L;

// функция находит максимальную разность углов прямоугольника:
// a[r1][c1] + a[r2][c2] - a[r1][c2] - a[r2][c1]
// возвращает 5 чисел: {разность, r1, r2, c1, c2}
// предполагается что nRows <= nCols
Tuple solve(int nRows, int nCols, const vector<vector<int64_t>> &a)
{
    // считаем лучший ответ для каждой пары строк
    // для фиксированной строки разность: a[r][c1] - a[r][c2]
    // формула из задачи преобразуется в вид:
    // (a[r1][c1] - a[r1][c2]) - (a[r2][c1] - a[r2][c2])
    // первую скобку делаем максимально возможной для каждого варианта второй скобки
    int64_t bestAnsw{-inf};
    int bestRow1{}, bestRow2{}, bestCol1{}, bestCol2{};
    for (int r1 = 0; r1 < nRows; r1++) {
        for (int r2 = r1 + 1; r2 < nRows; r2++) {
            // поддерживаем столбец с максимальной разностью среди уже пройденных:
            int64_t bestColDiff{-inf};
            int bestColIndex{-1};
            for (int c = 0; c < nCols; c++) {
                // разница в текущем столбце:
                int64_t currColDiff = a[r1][c] - a[r2][c];
                // обновляем лучший ответ:
                int64_t currAnsw = bestColDiff - currColDiff;
                if (bestAnsw < currAnsw) {
                    bestAnsw = currAnsw;
                    bestRow1 = r1;
                    bestRow2 = r2;
                    bestCol1 = bestColIndex;
                    bestCol2 = c;
                }
                // обновляем лучший столбец:
                if (bestColDiff < currColDiff) {
                    bestColDiff = currColDiff;
                    bestColIndex = c;
                }
            }
        }
    }
    return Tuple(bestAnsw, bestRow1, bestRow2, bestCol1, bestCol2);
}

// функция находит ответ для любого двумерного вектора
// если количество строк <= количеству столбцов, то сразу вызывает
// специализированную функцию перебора пары строк
// иначе переворачивает массив, делая строки столбцами, находит ответ
// для перевёрнутого массива, и возвращает его, приведя к ответу для оригинального
Tuple solve(const vector<vector<int64_t>> &arr) {
    const int nRows = (int)arr.size();
    const int nCols = (int)arr[0].size();
    if (nRows <= nCols) {
        return solve(nRows, nCols, arr);
    } else {
        vector a(nCols, vector<int64_t>(nRows));
        for (int r = 0; r < nRows; r++)
            for (int c = 0; c < nCols; c++) {
                a[c][r] = arr[r][c];
            }
        auto [maxRes, c1, c2, r1, r2] = solve(nCols, nRows, a);
        return Tuple(maxRes, r1, r2, c1, c2);
    }
}

main() {
    // ускорение ввода-вывода:
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем данные:
    int nRows, nCols;
    cin >> nRows >> nCols;
    vector a(nRows, vector<int64_t>(nCols));
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            cin >> a[r][c];
    // вызываем функцию решения и выводим ответ:
    auto [maxRes, r1, r2, c1, c2] = solve(a);
    if (maxRes < 0)
        cout << "-1\n";
    else
        cout << r1+1 << ' ' << r2+1 << ' ' << c1+1 << ' ' << c2+1 << '\n';
}