#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
void remin(auto &x, const auto &y) { if (x > y) x = y; }
bool getbit(int mask, int i) { return (mask >> i) & 1; }

using ld = long double;
const ld inf = 1e100L;

ld dist(std::complex<ld> a, std::complex<ld> b) {
// манхэттенское расстояние между двумя точками
    return std::abs(a.real() - b.real()) + std::abs(a.imag() - b.imag());
}
ld solve(const std::vector<std::complex<ld>> &pt) {
// за какое кратчайшее расстояние можем обойти все точки
// решение через динамику по подмножествам
// dp[i][subset] = за какое время можем посетить subset вершин остановившись в i-й вершине
    const int n = isz(pt);
    std::vector<std::vector<ld>> dp(n, std::vector<ld>(1 << n, +inf));
    for (int i = 0; i < n; i++) {
        dp[i][1 << i] = 0;
    }
    for (int mask = 0; mask < (1 << n); mask++)
        for (int from = 0; from < n; from++)
            if (getbit(mask, from))
                for (int to = 0; to < n; to++)
                    if (!getbit(mask, to))
                        remin(dp[to][mask | (1 << to)], dist(pt[to], pt[from]) + dp[from][mask]);
    ld answ = inf;
    for (int i = 0; i < n; i++)
        remin(answ, dp[i][(1 << n)-1]);
    return answ;
}
ld solve(ld dx, ld dy, const auto &pt) {
    // поворачиваем все точки на угол между новой осью и Ох:
    ld angle = std::atan2(dy, dx);
    std::vector<std::complex<ld>> pt2(isz(pt));
    for (int i = 0; i < isz(pt); i++) {
        pt2[i] = std::complex<ld>(pt[i].first, pt[i].second);
        pt2[i] *= std::polar(ld(1), -angle); // умножение на комплексную экспоненту для поворота
    }
    return solve(pt2);
}
main() {
    int n; std::cin >> n;
    std::vector<std::pair<int,int>> pt(n);
    for (auto &[x,y] : pt)
        std::cin >> x >> y;
    // перебираем прямую, которая будет одной осью
    // затем вращаем плоскость так, чтобы эта прямая совпала с осью Ох
    // затем запускаем коммивояжора
    ld answ = inf;
    for (int i = 0; i + 1 < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ld dx = pt[j].first - pt[i].first;
            ld dy = pt[j].second - pt[i].second;
            remin(answ, solve(dx, dy, pt));
        }
    }
    std::cout << std::fixed << std::setprecision(12);
    std::cout << answ << std::endl;
}
