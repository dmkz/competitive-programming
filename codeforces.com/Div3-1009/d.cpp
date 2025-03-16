#include <bits/stdc++.h>
int64_t SQR(int x) {
    return x * 1LL * x;
}
void solve() {
    int n, m; std::cin >> n >> m;
    std::vector<int> x(n), r(n);
    for (int i = 0; i < n; i++)
        std::cin >> x[i];
    for (int i = 0; i < n; i++)
        std::cin >> r[i];
    // сумма радиусов действительно важна
    // давайте решим задачу за O(сумма радиусов) = O(m)
    // переберём каждую окружность и все вертикальные линии внутри неё
    // для каждой координаты x посчитаем максимальный y, что
    // точка (x, y) покрывается хотя бы одной окружностью
    std::map<int, int> maxY;
    for (int i = 0; i < n; i++) {
        int yy = 0;
        for (int xx = x[i] - r[i]; xx <= x[i] + r[i]; xx++) {
            while (SQR(yy+1) + SQR(x[i] - xx) <= SQR(r[i]))
                yy++;
            while (SQR(yy) + SQR(x[i] - xx) > SQR(r[i]))
                yy--;
            maxY[xx] = std::max(maxY[xx], yy);
        }
    }
    // теперь считаем ответ:
    int64_t answ = 0;
    for (const auto &[_, y] : maxY)
        answ += 2 * y + 1;
    std::cout << answ << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
