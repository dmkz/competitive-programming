// диначеское программирование, implicit prefix trie, O(n * m)
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using ll = long long;
const ll inf = (ll)1e18L+7;
void remin(auto &x, const auto &y) { if (y < x) x = y; }
main() {
    // читаем данные
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m, k; std::cin >> n >> m >> k;
    std::vector<ll> c(m+1, 0);
    for (int i = 1; i <= m; i++)
        std::cin >> c[i];
    std::vector a(n, std::vector(m, 0));
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        for (int j = 0; j < m; j++)
            a[i][j] = (s[j] - '0');
    }
    // решаем задачу:
    std::function<ll(int,int,int,ll)> solve =
    [&](int l, int r, int colId, ll s) -> ll {
        // найдём для каждого разряда где начинаются его позиции
        if (l >= r)
            return s;
        if (colId >= m) {
            // все они дошли до финального столбца
            return s + (r-l) * c[m];
        }
        int begin[k]{}, end[k]{};
        for (int i = 0; i < k; i++)
            begin[i] = end[i] = -1;
        for (int i = l, j; i < r; i = j) {
            const auto item = a[i][colId];
            for (j = i; j < r && item == a[j][colId]; j++);
            if (i < j) {
                begin[item] = i;
                end[item] = j;
            }
        }
        ll answ = inf;
        for (int i = 0; i < k; i++) {
            int li = begin[i], ri = end[i];
            ll curr = solve(li, ri, colId+1, s+((r-l)-(ri-li))*c[colId]);
            remin(answ, curr);
        }
        return answ;
    };
    std::cout << solve(0, n, 0, 0) << std::endl;
}
