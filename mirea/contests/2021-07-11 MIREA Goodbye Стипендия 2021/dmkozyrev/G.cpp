#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using ll = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    // читаем исходные данные и сортируем:
    int n, q; std::cin >> n >> q;
    std::vector<int> a(n);
    for (auto &it : a) std::cin >> it;
    std::sort(all(a));
    // выгодно из максимума вычитать второй максимум
    // из третьего максимума четвертый
    // и т.д., то есть, если вектор посорчен, то:
    // a[n]-a[n-1]+a[n-2]-a[n-3]+a[n-4]-a[n-5]...
    // нужно знать знакочередующуюся сумму на префиксе и суффиксе чтобы
    // быстро посчитать ответ для любого x
    // считаем знакочередующуюся сумму на префиксе и на суффиксе:
    std::vector<ll> pref(n),suff(n);
    for (int i = 0; i < n; i++) {
        if (i > 0) pref[i] = a[i] - pref[i-1];
        else pref[i] = a[i];
    }
    for (int i = n-1; i >= 0; i--) {
        if (i+1 < n) suff[i] = a[i] - suff[i+1];
        else suff[i] = a[i];
    }
    // находим лучший ответ:
    ll answ = (ll)1e18L+10;
    while (q --> 0) {
        int x; std::cin >> x;
        int i = int(std::lower_bound(all(a),x)-a.begin());
        ll curr = (i-1 >= 0 ? pref[i-1] : 0LL) - x + (i < n ? suff[i] : 0LL);
        if (i % 2 == 1) {
            // нужно изменить знак
            curr *= -1;
        }
        answ = std::min(answ,curr);
    }
    std::cout << answ << std::endl;
    return 0;
}