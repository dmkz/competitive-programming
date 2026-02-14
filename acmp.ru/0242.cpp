// конструктив, bitset, O(n^3)
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using pii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
const int inf = (int)1e9+7;
int solveForRows(vvi a, int n, int color) {
// данная функция проверяет, можем ли мы покрасить все строки в цвет
// 'color', использовав при этом 0, 1 или 2 столбца
    int answ = n;
    vi cntInRow(n), cntInCol(n);
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++) {
            a[r][c] = (a[r][c] == color);
            cntInRow[r] += (a[r][c]);
            cntInCol[c] += (a[r][c]);
        }
    // сначала красим все строки, в которых >= 2 клеток:
    for (int r = 0; r < n; r++)
        if (cntInRow[r] >= 2) {
            for (int c = 0; c < n; c++) {
                cntInCol[c] -= (a[r][c]);
                a[r][c] = 1;
                cntInCol[c] += (a[r][c]);
            }
        }
    // остались строки, в которых 0 или 1 клетка
    int min = *std::min_element(all(cntInRow));
    if (min >= 2) // покраска завершена
        return answ;
    if (min == 0) {
        // есть строки, в которых 0 клеток
        // можем покрасить их минимум за 2 столбца, но нужно проверить,
        // возможно ли это вообще:
        int cnt = 0;
        for (int c = 0; c < n; c++)
            cnt += (cntInCol[c] >= 2);
        if (cnt >= 2)
            return answ+2;
        return inf;
    }
    // теперь надо проверить, можем ли мы за 1 столбец покрасить
    // пересечение строк:
    std::bitset<256> total;
    for (int c = 0; c < n; c++)
        total[c] = 1;
    for (int r = 0; r < n; r++)
        if (cntInRow[r] == 1) {
            std::bitset<256> temp;
            for (int c = 0; c < n; c++)
                temp[c] = (a[r][c] == 0);
            total &= temp;
        }
    for (int c = 0; c < n; c++)
        if (total[c] == 1 && cntInCol[c] >= 2)
            return answ+1;
    // иначе, если есть два столбца с cntInCol >= 2, то ответ answ+2
    int cnt = 0;
    for (int c = 0; c < n; c++)
        cnt += (cntInCol[c] >= 2);
    if (cnt >= 2)
        return answ+2;
    return inf;
}
int solve(vvi a, int n, int color) {
    int answ = solveForRows(a, n, color);
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            std::swap(a[i][j], a[j][i]);
    return std::min(answ, solveForRows(a, n, color));
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, k; std::cin >> n >> k;
    vvi a(n, vi(n));
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            std::cin >> a[r][c];
    pii res(inf, 0);
    for (int i = 1; i <= k; i++) {
        int curr = solve(a, n, i);
        res = std::min(res, pii(curr, i));
    }
    if (res.first == inf)
        res = {0, 0};
    std::cout << res.first << ' ' << res.second << std::endl;
}
