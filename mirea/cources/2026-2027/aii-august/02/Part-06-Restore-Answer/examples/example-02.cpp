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
    // dp[i] хранит длину LIS, которая заканчивается в позиции i.
    vector<int> dp(n, 1), parent(n, -1);
    int finish = 0;
    for (int i = 0; i < n; i++) {
        // Выбираем предпоследний элемент, который даёт максимальную длину.
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        // Запоминаем конец лучшей подпоследовательности среди уже обработанных.
        if (dp[i] > dp[finish]) finish = i;
    }
    // Идём по предкам от конца и разворачиваем выбранную подпоследовательность.
    vector<ll> sequence;
    for (int i = finish; i != -1; i = parent[i])
        sequence.push_back(a[i]);
    reverse(sequence.begin(), sequence.end());
    // Выводим длину и значения одной наибольшей подпоследовательности:
    cout << sequence.size() << '\n';
    for (auto it : sequence)
        cout << it << ' ';
    cout << '\n';
}