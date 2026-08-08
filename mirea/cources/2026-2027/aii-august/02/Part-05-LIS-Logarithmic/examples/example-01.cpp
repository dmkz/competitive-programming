#include <bits/stdc++.h>
using namespace std;
using ll = long long;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Читаем последовательность:
    int n; cin >> n;
    vector<ll> a(n);
    for (auto& it : a)
        cin >> it;
    // Инициализируем пустую подпоследовательность и недостижимые длины:
    const ll inf = 1LL << 60;
    vector<ll> dp(n + 1, inf);
    dp[0] = -inf;
    int answ = 0;
    // Обрабатываем каждое число бинарным поиском:
    for (int i = 0; i < n; i++) {
        int pos = lower_bound(dp.begin() + 1, dp.end(), a[i]) - dp.begin();
        dp[pos] = a[i];
        answ = max(answ, pos);
    }
    // Выводим длину лучшей подпоследовательности:
    cout << answ << '\n';
}