// математика, реализация, формулы
// Задача: A, Вердикт: OK, Время: 0.001 сек, Память: 2 МБ
#include <bits/stdc++.h>
#include <cassert>
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n; std::cin >> n;
    int lastScore = 0, penalty = 0, wrong = 0;
    while (n --> 0) {
        int t, d; std::cin >> t >> d;
        if (d > lastScore) {
            // успешная попытка
            int diff = (d - lastScore);
            penalty += diff * t / 100 + 60 * wrong;
            wrong = 0;
            lastScore = d;
        } else {
            assert(d == lastScore);
            wrong++;
        }
    }
    std::cout << lastScore << ' ' << penalty << std::endl;
}
