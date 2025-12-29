// строки, реализация
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
void remin(auto &x, const auto &y) { if (y < x) x = y; }
int diff(const std::string &a, const std::string &b) {
    assert(isz(a) == isz(b));
    int answ{};
    for (int i = 0; i < isz(a); i++)
        answ += (a[i] != b[i]);
    return answ;
}
void solve() {
    int n; std::cin >> n;
    std::string s; std::cin >> s;
    int answ = n;
    for (int i = 0; i + 3 < n; i++)
        remin(answ, diff(s.substr(i, 4), "2026"));
    // либо убрать все вхождения 2025:
    int answ2{};
    for (int i = 0; i + 3 < n; i++)
        answ2 += (s.substr(i, 4) == "2025");
    std::cout << std::min(answ, answ2) << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
