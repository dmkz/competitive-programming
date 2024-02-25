#include <bits/stdc++.h>
using namespace std;
void solve() {
    int divisor, k; cin >> divisor >> k;
    // надо найти k-е натуральное, которое не делится на divisor
    // значит до него (включительно) k чисел не делятся на divisor
    // и причём найденное число будет минимальным среди всех натуральных чисел,
    // до которых >= k чисел не делятся на divisor
    // по этому критерию работает монотонность,
    // поэтому можем запустить бинпоиск по ответу
    int64_t low = 0, high = (int64_t)1e18L;
    while (high - low > 1) {
        int64_t mid = (low + high) / 2;
        // сколько чисел до него (включительно) делятся на делитель?
        int64_t nDivisible = mid / divisor;
        // все остальные не деляется:
        int64_t nNotDivisible = mid - nDivisible;
        // проверяем условие и двигаем границу:
        if (nNotDivisible >= k)
            high = mid;
        else
            low = mid;
    }
    cout << high << "\n";
}
main() {
    // ускорение ввода-вывода
    ios::sync_with_stdio(false);
    cin.tie(0);
    // мультитесты
    int tt; cin >> tt;
    while (tt --> 0)
        solve();
}
