#include <bits/stdc++.h>
#include <bits/extc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using ll = long long;
// решение задачи:
void solve() {
    int n; ll k; cin >> n >> k;
    // найдём период. для этого храним пары (позиция, шаг % n). они задают последовательность переходов
    // при попытке хранить пары в set<pair<int,int>> получил Time Limit Exceeded.
    // поэтому храним вектор отсортированных векторов.
    vector cache(n, vector<int>{});
    int pos = 0, i, period = -1;
    for (i = 1; i <= k; i++) {
        // делаем переход:
        (pos += i) %= n;
        // мы уже были тут? смотрим сохранённые шаги и обновляем их
        auto it = lower_bound(all(cache[pos]), i%n);
        if (it != cache[pos].end() && *it == i % n) {
            period = i-1;
            break;
        }
        cache[pos].insert(it, i%n);
    }
    // нашли период, теперь эмулируем заново, но из k вычитаем чётное число периодов
    if (period != -1 && k >= 2 * period)
        k -= (k / (2 * period)) * 2 * period;
    vector<char> a(n, false);
    pos = 0;
    for (i = 1; i <= k; i++) {
        (pos += i) %= n;
        a[pos] ^= 1;
    }
    // считаем и выводим ответ:
    int answ{};
    for (i = 0; i < n; i++)
        answ += a[i];
    cout << answ << '\n';
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int tt = 1; cin >> tt;
    while (tt --> 0) solve();
    return 0;
}
