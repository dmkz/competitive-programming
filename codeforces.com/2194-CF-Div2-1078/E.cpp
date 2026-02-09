// графы, динамическое программирование, жадные алгоритмы, путь через клетку
#include <bits/stdc++.h>
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using ll = long long;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using pll = std::pair<ll,ll>;
using vpll = std::vector<pll>;
const ll inf = (ll)1e18L;
void remax(auto &x, const auto &y) { if (x < y) x = y; }
void remin(auto &x, const auto &y) { if (y < x) x = y; }
void solve() {
    int nRows, nCols;
    std::cin >> nRows >> nCols;
    vvi a(nRows, vi(nCols));
    for (auto &row : a) for (auto &it : row) std::cin >> it;
    // динамика от старта до текущей клетки
    vvl dpS(nRows, vl(nCols, -inf));
    dpS[0][0] = a[0][0];
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++) {
            if (r - 1 >= 0)
                remax(dpS[r][c], dpS[r-1][c] + a[r][c]);
            if (c - 1 >= 0)
                remax(dpS[r][c], dpS[r][c-1] + a[r][c]);
        }
    // динамика от текущей клетки до финиша
    vvl dpF(nRows, vl(nCols, -inf));
    dpF.back().back() = a.back().back();
    for (int r = nRows-1; r >= 0; r--)
        for (int c = nCols-1; c >= 0; c--) {
            if (r + 1 < nRows)
                remax(dpF[r][c], dpF[r+1][c] + a[r][c]);
            if (c + 1 < nCols)
                remax(dpF[r][c], dpF[r][c+1] + a[r][c]);
        }
    // для каждой клетки найдём лучший путь, проходящий через неё
    vvl dp(nRows, vl(nCols));
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            dp[r][c] = dpS[r][c] + dpF[r][c] - a[r][c];
    // Идея такая: вот он заблочил клетку на диагонали нам
    // Если путь через неё не был максимальным для этой диагонали, то
    // ничего плохого для нас не случилось. Иначе мы идём через второй
    // максимальный путь.
    // Для каждой диагонали найдём максимум и второй максимум:
    vpll diag(nRows+nCols-1, pll(-inf, -inf));
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++) {
            auto &[fi, se] = diag[r+c];
            ll res = dp[r][c];
            if (res >= fi) {
                se = fi;
                fi = res;
            } else if (res >= se)
                se = res;
        }
    // теперь наш оппонент блочит клетку, и если она была максимумом
    // то идём через второй максимум
    ll answ = inf;
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++) {
            // он нам перевернул этот элемент, но мы
            // всё равно через него идём:
            ll curr = dpS[r][c] + dpF[r][c] - a[r][c];
            curr -= 2 * a[r][c];
            // либо мы идём через второй максимум:
            if (dp[r][c] == diag[r+c].first)
                remax(curr, diag[r+c].second);
            else
                remax(curr, diag[r+c].first);
            // обновляем ответ:
            remin(answ, curr);
        }
    std::cout << answ << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0)
        solve();
}