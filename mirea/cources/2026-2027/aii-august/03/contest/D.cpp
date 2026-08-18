#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using ll = long long;
const ll inf = 1LL << 60;
void setmax(auto &x, const auto &y) { if (x < y) x = y; }
void solve() {
    // читаем все доступные данные:
    int nRows, nCols, q;
    cin >> nRows >> nCols >> q;
    vector a(nRows, vector<int>(nCols));
    for (auto &row : a)
        for (auto &it : row)
            cin >> it;
    vector<int> rows(q), cols(q);
    for (auto &it : rows) cin >> it;
    for (auto &it : cols) cin >> it;
    // считаем две динамики: прямую (1, 1) -> (n, m) и обратную (n, m) -> (1, 1)
    vector dpS(nRows, vector(nCols, -inf));
    vector dpF(nRows, vector(nCols, -inf));
    dpS[0][0] = a[0][0];
    dpF[nRows-1][nCols-1] = a[nRows-1][nCols-1];
    // переходы для прямой динамики:
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++) {
            if (r > 0) setmax(dpS[r][c], a[r][c] + dpS[r-1][c]);
            if (c > 0) setmax(dpS[r][c], a[r][c] + dpS[r][c-1]);
        }
    // переходы для обратной динамики:
    for (int r = nRows-1; r >= 0; r--)
        for (int c = nCols-1; c >= 0; c--) {
            if (r + 1 < nRows) setmax(dpF[r][c], a[r][c] + dpF[r+1][c]);
            if (c + 1 < nCols) setmax(dpF[r][c], a[r][c] + dpF[r][c+1]);
        }
    // отвечаем на запросы:
    for (int i = 0; i < q; i++) {
        const int r = rows[i]-1, c = cols[i]-1;
        ll res = dpS[r][c] + dpF[r][c] - a[r][c];
        cout << res << '\n';
    }
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
