#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
void solve() {
    // читаем данные:
    int n; cin >> n;
    vector<int> a(n);
    for (auto &it : a) cin >> it;
    // лестница - комбинация из двух подпоследовательностей: возрастающей и убывающей
    // для каждой позиции считаем количество возрастающих
    // подпоследовательностей, заканчивающихся в ней:
    vector<int> dpL(n, 1);
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[j] < a[i])
                (dpL[i] += dpL[j]) %= mod;
    // зеркально для каждой позиции считаем количество убывающих
    // подпоследовательностей, начинающихся в ней:
    vector<int> dpR(n, 1);
    for (int i = n-2; i >= 0; i--)
        for (int j = i+1; j < n; j++)
            if (a[j] < a[i])
                (dpR[i] += dpR[j]) %= mod;
    // считаем и выводим ответ:
    int64_t answ = 0;
    for (int i = 0; i < n; i++)
        (answ += dpL[i] * 1LL * dpR[i]) %= mod;
    cout << answ << '\n';
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
