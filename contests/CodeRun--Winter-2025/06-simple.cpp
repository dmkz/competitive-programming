// сортировка, бинарный поиск, сумма расстояний
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using ll = long long;
std::tuple<int,int,int>
countLEG(const auto &v, int px) {
    int nLess = int(std::lower_bound(all(v), px) - v.begin());
    int nGreater = int(v.end() - std::upper_bound(all(v), px));
    int nEqual = isz(v) - nLess - nGreater;
    return {nLess, nEqual, nGreater};
}
void solve() {
    // читаем данные, сортируем координаты, считаем их сумму:
    int n, m;
    std::cin >> n >> m;
    std::vector<int> x(n), y(n);
    ll answ{};
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
        answ += std::abs(x[i]) + std::abs(y[i]);
    }
    std::sort(all(x));
    std::sort(all(y));
    // обрабатываем перемещения и отвечает на запросе
    std::string s; std::cin >> s;
    int px{}, py{};
    assert(isz(s) == m);
    for (const auto &dir : s) {
        if (dir == 'N') {
            auto [l,e,g] = countLEG(y, py);
            answ += (l+e)-g;
            py++;
        } else if (dir == 'S') {
            auto [l,e,g] = countLEG(y, py);
            answ += (g+e)-l;
            py--;
        } else if (dir == 'W') {
            auto [l,e,g] = countLEG(x, px);
            answ += (g+e)-l;
            px--;
        } else if (dir == 'E') {
            auto [l,e,g] = countLEG(x, px);
            answ += (l+e)-g;
            px++;
        }
        std::cout << answ << "\n";
    }
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    solve();
}
