// жадные алгоритмы, конструктив
#include <bits/stdc++.h>
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using ll = long long;
void solve() {
    int nRows, nCols;
    std::cin >> nRows >> nCols;
    vvi a(nRows, vi(nCols));
    int s = 0;
    for (auto &row : a)
        for (auto &it : row)
            std::cin >> it, s += it;
    // мы можем любое разбиение получить
    int half = s / 2;
    // формально: надо выбрать неубывающую
    // последовательность длин в каждом столбце
    vi len(nCols, 0), sum(nCols, 0);
    ll right{}, left{};
    for (int col = nCols-1; col >= 0; col--) {
        while (half > 0 && len[col] < nRows &&
               (col == nCols-1 || len[col] < len[col+1]))
        {
            int r = len[col]++;
            half -= a[r][col];
            sum[col] += a[r][col];
            right += a[r][col];
        }
    }
    left = s - right;
    std::cout << left * right << "\n";
    // восстанавливаем ответ:
    int r = 0;
    std::string answ;
    for (int c = 0; c < nCols; c++) {
        while (r < len[c]) {
            answ += 'D';
            r++;
        }
        assert(r == len[c]);
        answ += 'R';
    }
    while (r < nRows)
        answ += 'D', r++;
    std::cout << answ << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
