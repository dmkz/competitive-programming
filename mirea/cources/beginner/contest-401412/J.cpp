#include <bits/stdc++.h>
using namespace std;
void solveOneTest() {
    // читаем исходные данные:
    int nRects, nQueries;
    cin >> nRects >> nQueries;
    // sums - двумерный вектор. Первый индекс - высота, второй индекс - ширина
    // используем то, что высота и ширина от 1 до 1000
    // 1024 взято с небольшим запасом (точно хватит и не слишком много взяли)
    // также используем автоматическое определение содержимого вектора из C++17
    vector sums(1024, vector(1024, 0LL));
    while (nRects --> 0) {
        int h, w; cin >> h >> w;
        // сначало к sums[h][w] прибавляем площадь очередного треугольника с
        // высотой `h` и шириной `w`:
        sums[h][w] += int64_t(h) * w;
    }
    // теперь начинаем считать префикс-суммы в том же массиве
    // sums[h][w] = сумма площадей всех прямоугольников с высотой <= h и шириной <= w
    for (int i = 1; i < 1024; i++) // высота, 1-индексация, можем не бояться делать i-1
        for (int j = 1; j < 1024; j++) // ширина, 1-индексация, можем не бояться делать j-1
            sums[i][j] += sums[i-1][j] + sums[i][j-1] - sums[i-1][j-1];
    // отвечаем на запросы:
    while (nQueries --> 0) {
        int hs, ws, hb, wb;
        cin >> hs >> ws >> hb >> wb;
        hb--, wb--;
        cout << (sums[hb][wb] - sums[hb][ws] - sums[hs][wb] + sums[hs][ws]) << '\n';
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int nTests; cin >> nTests;
    while (nTests --> 0) solveOneTest();    
}