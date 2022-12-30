#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#include "../SparseTable.hpp"
using vi = std::vector<int>;
using vvi = std::vector<vi>;
bool check(int x, vvi a) {
    for (int rotate = 0; rotate < 2; rotate++) {
        // считаем для строк
        for (int r = 0; r < isz(a); r++) {
            // строим спарсу для каждой строки:
            SparseTable<int, Min<int>> st(a[r]);
            int c;
            for (c = 0; c + x - 1 < isz(a[r]); c++)
                a[r][c] = st.calcFunc(c, c + x - 1);
            a[r].resize(c);
        }
        // транспонируем
        vvi b(isz(a[0]), vi(isz(a)));
        for (int r = 0; r < isz(a); r++)
            for (int c = 0; c < isz(a[r]); c++)
                b[c][r] = a[r][c];
        a = b;
    }
    for (int r = 0; r < isz(a); r++) {
        assert(isz(a[r]));
        if (*std::max_element(all(a[r])) >= x)
            return true;
    }
    return false;
}
int solve(int nRows, int nCols, const vvi &a) {
    int low = 0, high = std::min(nRows, nCols)+1;
    while (high - low > 1) {
        int mid = (low+high)/2;
        if (check(mid,a)) low = mid;
        else high = mid;
    }
    return low;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt--) {
        int n, m; std::cin >> n >> m;
        vvi a(n, vi(m));
        for (auto &row : a)
            for (auto &it : row)
                std::cin >> it;
        std::cout << solve(n,m,a) << '\n';
    }
    return 0;
}