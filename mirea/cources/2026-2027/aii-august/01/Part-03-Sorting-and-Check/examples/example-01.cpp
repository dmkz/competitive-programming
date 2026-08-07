#include <bits/stdc++.h>
using namespace std;
bool check(const auto& a, int64_t x, int64_t k, int mid) {
    // Считаем цену подготовки mid наибольших чисел.
    int64_t need = 0;
    for (int i = 0; i < mid; i++) {
        need += max(0LL, x - a[i]);
        if (need > k) return false;
    }
    return true;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Читаем числа, запас увеличений и порог.
    int n; int64_t k, x;
    cin >> n >> k >> x;
    vector<int64_t> a(n);
    for (auto& it : a) cin >> it;
    // Сортируем по убыванию, чтобы улучшать первые элементы.
    sort(a.rbegin(), a.rend());
    // Ищем наибольшее достижимое количество подготовленных чисел.
    int low = 0, high = n + 1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (check(a, x, k, mid)) low = mid;
        else high = mid;
    }
    // Выводим максимальное количество.
    cout << low << '\n';
}