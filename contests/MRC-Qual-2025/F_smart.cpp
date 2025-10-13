// Задача: F, Вердикт: OK, Время: 0.195s, Память: 26.81Mb
#include <bits/stdc++.h>
using namespace std;
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
    // проверяем существование положительного ответа
    // достаточно проверять квадраты 2х2, потому что, если существует
    // ответ в виде прямоугольника, то существует и ответ в виде квадрата 2x2
    // это возможно, потому что нас не просят находить лучший ответ, а просто
    // найти любой, где сумма красных минус сумма синих больше нуля
    vector<int> answer = {-1};
    bool found = false;
    for (int r = 0; !found && r + 1 < nRows; r++)
        for (int c = 0; !found && c + 1 < nCols; c++) {
            int64_t diff = a[r][c] + a[r+1][c+1] - a[r][c+1] - a[r+1][c];
            if (diff > 0) {
                // координаты квадрата 2х2 в 1-индексации:
                answer = {r+1, r+2, c+1, c+2};
                found = true;
                break;
            }
        }
    for (auto it : answer)
        cout << it << ' ';
    cout << '\n';
}
