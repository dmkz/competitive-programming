// динамическое программирование, двуслойная динамика, комбинаторика
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using vi = std::vector<int>;
using ll = long long;
void solve() {
    // читаем данные
    int n; std::cin >> n;
    vi a(n), b(n), c(n);
    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    for (int i = 0; i < n; i++)
        std::cin >> b[i];
    for (int i = 0; i < n; i++)
        std::cin >> c[i];
    // дублируем снеговиков
    for (int i = 0; i < n; i++)
        a.push_back(a[i]);
    for (int i = 0; i < n; i++)
        b.push_back(b[i]);
    for (int i = 0; i < n; i++)
        c.push_back(c[i]);
    // считаем
    vi dpABCurr(2*n+1);
    vi dpABNext(2*n+1);
    vi dpCBCurr(2*n+1);
    vi dpCBNext(2*n+1);
    ll answ{};
    for (int j = 2 * n - 1; j >= 0; j--) {
        std::fill(all(dpABCurr), 0);
        std::fill(all(dpCBCurr), 0);
        ll cntA{}, cntC{};
        for (int i = 2 * n - 1; i >= 0; i--) {
            if (a[i] < b[j])
                dpABCurr[i] = dpABNext[i+1] + 1;
            else
                dpABCurr[i] = 0;
        }
        for (int i = 2 * n - 1; i >= 0; i--) {
            if (b[j] < c[i])
                dpCBCurr[i] = dpCBNext[i+1] + 1;
            else
                dpCBCurr[i] = 0;
        }
        for (int i = 0; i < n; i++)
            cntA += (dpABCurr[i] >= n);
        for (int i = 0; i < n; i++)
            cntC += (dpCBCurr[i] >= n);
        if (0 <= j && j < n)
            answ += cntA * cntC;
        std::swap(dpCBCurr, dpCBNext);
        std::swap(dpABCurr, dpABNext);
    }
    std::cout << answ << "\n";
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
