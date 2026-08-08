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
    // dp[k] хранит минимальное окончание длины k и его индекс.
    const ll inf = 1LL << 60;
    vector<pair<ll, int>> dp(n + 1, {inf, -1});
    vector<int> parent(n, -1);
    dp[0] = {-inf, -1};
    int answ = 0;
    for (int i = 0; i < n; i++) {
        // Пара с индексом -1 идёт раньше всех окончаний с таким же значением.
        int pos = lower_bound(dp.begin() + 1, dp.end(), pair<ll, int>{a[i], -1}) - dp.begin();
        // Предыдущая длина хранит индекс предшественника для нового окончания.
        parent[i] = dp[pos - 1].second;
        dp[pos] = {a[i], i};
        answ = max(answ, pos);
    }
    // Идём по предкам от конца максимальной длины и разворачиваем ответ.
    vector<ll> sequence;
    for (int i = dp[answ].second; i != -1; i = parent[i])
        sequence.push_back(a[i]);
    reverse(sequence.begin(), sequence.end());
    // Выводим длину и значения одной наибольшей подпоследовательности:
    cout << sequence.size() << '\n';
    for (auto it : sequence)
        cout << it << ' ';
    cout << '\n';
}