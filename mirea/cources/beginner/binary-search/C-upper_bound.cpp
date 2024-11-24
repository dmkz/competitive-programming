#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // строим префикс суммы
    vector<int64_t> s(n);
    s[0] = a[0];
    for (int i = 1; i < n; i++)
        s[i] = s[i-1] + a[i];
    // отвечаем на запросы
    int64_t accumulatedDamage = 0; // накопленный урон
                                   // Тор воскрешает всех когда все умрут 
    while (q --> 0) {
        int64_t k; cin >> k;
        accumulatedDamage += k;
        // находим префикс, который был убит накопленным уроном:
        //int low = -1, high = n;
        //while (high - low > 1) {
        //    int mid = (low + high) / 2;
        //    if (s[mid] <= accumulatedDamage)
        //        low = mid;
        //    else
        //        high = mid;
        //}
        int high = upper_bound(s.begin(), s.end(), accumulatedDamage) - s.begin();
        // [0, low] - умерли
        // [high, n) - живы
        int countAlive = n - high; // количество живых
        if (countAlive == 0) { // все оживают
            countAlive = n;
            accumulatedDamage = 0;
        }
        cout << countAlive << "\n";
    }
}
