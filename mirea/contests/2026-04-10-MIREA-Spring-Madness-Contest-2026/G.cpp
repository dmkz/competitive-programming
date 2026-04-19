// префиксные суммы, бинарный поиск, O(n + q * log(n))
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q, h, w;
    cin >> n >> q >> h >> w;
    vector<int> a(n);
    vector<ll> sh(n+1), sw(n+1), s(n+1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sw[i+1] = sw[i], sh[i+1] = sh[i];
        if (i % 2 == 0) sh[i+1] += a[i];
        else sw[i+1] += a[i];
        s[i+1] = s[i] + a[i];
    }
    auto f = [&](ll t) {
        if (t > s.back())
            t = s.back();
        auto i = int(upper_bound(s.begin(), s.end(), t) - s.begin() - 1);
        assert(0 <= i && i < (int)s.size());
        ll coeffH = sh[i], coeffW = sw[i];
        if (i % 2 == 0) coeffH += t - s[i];
        else coeffW += t - s[i];
        return h * 1LL * w + coeffH * h + coeffW * w;
    };
    while (q --> 0) {
        ll l, r; cin >> l >> r;
        cout << f(r) - f(l) << '\n';
    }
}
