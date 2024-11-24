#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, maxWater;
    cin >> n >> maxWater;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // ответ может быть до 2*10^9
    // будем искать бинарным поиском высоту аквариума
    int low = 0, high = 2e9+1;
    while (high - low > 1) {
        int mid = low + (high - low) / 2; // избегаем переполнения
        // считаем сколько воды понадобится для такой высоты
        int64_t needWater = 0;
        for (int i = 0; i < n; i++)
            needWater += max(0, mid - a[i]);
        // обновляем границу
        if (needWater <= maxWater)
            low = mid;
        else
            high = mid;
    }
    // выводим ответ
    assert(low >= 1);
    cout << low << "\n";
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int numTests; cin >> numTests;
    while (numTests --> 0)
        solve();
}
