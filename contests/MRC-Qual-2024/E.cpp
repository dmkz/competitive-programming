#include <bits/stdc++.h>
using ld = long double;
using ll = long long;
main() {
    // читаем n точек:
    int n; std::cin >> n;
    std::vector<std::pair<int,int>> pt(n);
    for (auto &[x,y] : pt)
        std::cin >> x >> y;
    // считаем ответ:
    ld answ = 0;
    for (int i = 1; i < n; i++) {
        // если векторы (pt[i] - pt[i-1]) и (pt.back() - pt[i-1])
        // параллельны, то прибавим к ответу расстояние между i и i-1
        int dxI = pt[i].first - pt[i-1].first;
        int dyI = pt[i].second - pt[i-1].second;
        int dxN = pt.back().first - pt[i-1].first;
        int dyN = pt.back().second - pt[i-1].second;
        // векторное произведение параллельных векторов равно нулю
        // проверим это:
        ll cross = dxI * 1LL * dyN - dyI * 1ll * dxN;
        if (cross == 0)
            answ += std::sqrt(ld(dxI * dxI + dyI * dyI));
    }
    std::cout << std::fixed << std::setprecision(12);
    std::cout << answ << std::endl;
}
