#include <bits/stdc++.h>
using namespace std;
using ll = long long;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Читаем награды ступеней:
    int n; cin >> n;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    function<ll(int)> best = [&](int i) {
        if (i == n) return 0LL;
        const ll neg = -(1LL << 60);
        ll answ = neg;
        // Перебираем все следующие прыжки без запоминания ответов.
        for (int jump : {1, 2})
            if (i + jump <= n)
                answ = max(answ, a[i + jump] + best(i + jump));
        return answ;
    };
    cout << best(0) << '\n';
}