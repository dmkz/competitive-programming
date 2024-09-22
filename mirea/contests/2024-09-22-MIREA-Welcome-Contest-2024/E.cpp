#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(1+n+1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    // предподсчитываем суммы на префиксе:
    vector<ll> prefMultiplied(1+n+1), suffMultiplied(1+n+1), prefSum(1+n+1);
    for (int i = 1; i <= n; i++) {
        prefMultiplied[i] = prefMultiplied[i-1] + (ll)(i) * a[i];
        prefSum[i] = prefSum[i-1] + a[i];
    }
    // и на суффиксе:
    for (int i = n; i >= 1; i--)
        suffMultiplied[i] = suffMultiplied[i+1] + ll(n-i+1) * a[i];
    
    // отвечаем на запросы:
    while (q --> 0) {
        int L, R; cin >> L >> R;
        // до середины - возрастает, затем убывает
        int mid = (L+R)/2;
        ll left = prefMultiplied[mid] - prefMultiplied[L-1];
        left -= (prefSum[mid] - prefSum[L-1])*(L-1);
        // сумму справа:
        ll right = suffMultiplied[mid+1] - suffMultiplied[R+1];
        right -= (prefSum[R] - prefSum[mid]) * (n-R);
        // выводим ответ:
        cout << left + right << "\n";
    }
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0)
        solve();
}
