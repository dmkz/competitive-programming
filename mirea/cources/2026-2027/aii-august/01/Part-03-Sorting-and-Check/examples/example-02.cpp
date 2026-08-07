#include <bits/stdc++.h>
using namespace std;
bool check(const auto& a, const auto& b, int64_t k, int mid) {
    // Считаем цену mid запланированных побед.
    int64_t need = 0;
    int firstWin = a.size() - mid;
    for (int i = 0; i < mid; i++) {
        need += max(0LL, b[i] - a[firstWin + i]);
        if (need > k) return false;
    }
    return true;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Читаем оба мультимножества и запас увеличений.
    int n; int64_t k; cin >> n >> k;
    vector<int64_t> a(n), b(n);
    for (auto& it : a) cin >> it;
    for (auto& it : b) cin >> it;
    // Сортируем, чтобы сопоставлять малые и большие значения по ролям.
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    // Ищем наибольшее достижимое количество побед.
    int low = 0, high = n + 1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (check(a, b, k, mid)) low = mid;
        else high = mid;
    }
    // Выводим максимальное количество побед.
    cout << low << '\n';
}