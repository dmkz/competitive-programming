// перебор, пересечение множеств, bitset, конструктив
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
void remin(auto &x, const auto &y) { if (y < x) x = y; }
using vi = std::vector<int>;
void solve() {
    // читаем данные и находим множество букв для каждого столбца:
    int nCols, nRows;
    std::cin >> nCols >> nRows;
    std::vector<std::bitset<26>> cols(nCols);
    for (int r = 0; r < nRows; r++) {
        std::string s;
        std::cin >> s;
        for (int c = 0; c < nCols; c++)
            cols[c][s[c]-'a'] = 1;
    }
    // находим делители количества столбцов:
    vi t;
    for (int x = 1; x * x <= nCols; x++)
        if (int y = nCols / x; y * x == nCols) {
            t.push_back(x);
            if (x != y)
                t.push_back(y);
        }
    std::sort(all(t));
    std::pair<int, std::string> answ{INT_MAX,{}};
    for (int L : t) {
        std::vector<std::bitset<26>> temp(L);
        for (int i = 0; i < L; i++)
            temp[i] = cols[i];
        for (int i = L; i < nCols; i++)
            temp[i % L] &= cols[i];
        bool ok = true;
        for (int i = 0; i < L; i++)
            ok &= (temp[i].count() > 0);
        if (ok && answ.first > L) {
            std::string s(L, 'a');
            for (int i = 0; i < L; i++)
                s[i] += (int)temp[i]._Find_first();
            remin(answ, std::make_pair(L, s));
        }
    }
    auto [L, tt] = answ;
    std::string res = tt;
    for (int i = 1; i < nCols / L; i++)
        res += tt;
    std::cout << res << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
