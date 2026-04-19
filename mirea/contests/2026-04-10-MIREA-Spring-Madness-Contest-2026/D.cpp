// математика, жадные алгоритмы, O(n)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll solve(int n, ll k, const vector<int> &a) {
    ll sum = 0, mx = 0;
    for (int i = 0; i < n; ++i) {
        ll x = a[i];
        sum += x;
        mx = max(mx, x);
    }
    ll answ, others = sum - mx;
    if (mx <= others + 1)
        answ = k * sum - (k - 1) * 1LL * n;
    else
        answ = k * (2 * others + 1) - (k - 1) * 1LL * (n - 1);
    return answ;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while (t --> 0) {
        int n; ll k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        cout << solve(n, k, a) << '\n';
    }
}