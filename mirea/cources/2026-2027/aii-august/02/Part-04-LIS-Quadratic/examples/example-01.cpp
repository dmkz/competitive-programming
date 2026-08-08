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
    // Инициализируем длину подпоследовательности из одного элемента:
    vector<int> dp(n, 1);
    // Перебираем возможные предпоследние элементы:
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
    // Выводим длину лучшей подпоследовательности:
    int answ = 0;
    for (auto it : dp)
        answ = max(answ, it);
    cout << answ << '\n';
}