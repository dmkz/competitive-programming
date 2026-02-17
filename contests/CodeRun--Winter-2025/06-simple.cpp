// сортировка, бинарный поиск, сумма расстояний
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using ll = long long;
int countLess(const auto &v, int px) {
    return int(std::lower_bound(all(v), px) - v.begin());
}
int countGreater(const auto &v, int px) {
    return int(v.end() - std::upper_bound(all(v), px));
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
            answ += n - 2 * countGreater(y, py);
            py++;
        } else if (dir == 'S') {
            answ += n - 2 * countLess(y, py);
            py--;
        } else if (dir == 'W') {
            answ += n - 2 * countLess(x, px);;
            px--;
        } else if (dir == 'E') {
            answ += n - 2 * countGreater(x, px);
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
