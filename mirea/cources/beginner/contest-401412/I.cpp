#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем исходные данные:
    int n, nQueries;
    cin >> n >> nQueries;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // считаем префикс-суммы:
    vector<int64_t> pref(n+1);
    for (int i = 0; i < n; i++)
        pref[i+1] = pref[i] + a[i];
    // отвечаем на запросы: бинпоиском найдём, сколько чуваков умрёт от
    // накопленного урона. Остальные выживут. Надо учесть воскрешение.
    int64_t accumulatedDamage = 0; // будем считать накопленный урон
    while (nQueries --> 0) {
        int64_t nShots; cin >> nShots;
        accumulatedDamage += nShots;
        // находим, сколько чуваков умрут от `accumulatedDamage` урона
        // low - мин. количество умерших
        // high - макс. количество умерших плюс один
        int low = 0, high = n+1;
        while (high - low > 1) {
            // проверим, умрут ли mid чуваков от данного урона
            int mid = (low + high) / 2;
            // если сумма здоровья первых mid чуваков <= урон
            if (pref[mid] <= accumulatedDamage)
                low = mid; // сдохли
            else
                high = mid; // не сдохли
        }
        // после бинпоиска: low чуваков сдохнут, значит (n - low) выживут!
        int nAlive = n - low;
        if (nAlive == 0) {
            accumulatedDamage = 0; // накопленный урон нивелируется
            nAlive = n; // все чуваки воскресают
        }
        cout << nAlive << '\n';
    }
}