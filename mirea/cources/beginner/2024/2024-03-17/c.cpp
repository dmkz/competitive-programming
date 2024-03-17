#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем таблицу:
    int nRows, nCols;
    cin >> nRows >> nCols;
    vector a(nRows, vector(nCols, 0));
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            cin >> a[r][c];
    // перебираем, куда поставим слона, и считаем сумму вручную
    int bestSum = 0;
    for (int row = 0; row < nRows; row++)
        for (int col = 0; col < nCols; col++) {
            // в клетку (row, col) мы поставим слона. считаем сумму
            int sum = a[row][col];
            {   // вправо-вверх
                int r = row-1, c = col+1;
                while (r >= 0 && c < nCols) {
                    sum += a[r][c];
                    r--;
                    c++;
                }
            }
            {   // влево-вверх
                int r = row-1, c = col-1;
                while (r >= 0 && c >= 0) {
                    sum += a[r][c];
                    r--;
                    c--;
                }
            }
            {   // вправо-вниз
                int r = row+1, c = col+1;
                while (r < nRows && c < nCols) {
                    sum += a[r][c];
                    r++;
                    c++;
                }
            }
            {   // влево-вниз
                int r = row+1, c = col-1;
                while (r < nRows && c >= 0) {
                    sum += a[r][c];
                    r++;
                    c--;
                }
            }
            // обновляем ответ
            if (sum > bestSum)
                bestSum = sum;
        }
    cout << bestSum << endl;
}
int main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
