// префиксные суммы, бинарный поиск, геометрия, площадь сектора, O(n + q * log(n))
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using ld = long double;
using ll = long long;
const ld pi = acosl(-1.0L);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int n, q, R; 
    cin >> n >> q >> R;

    vector<ll> sa(1 + n);
    for (int i = 1; i <= n; i++) {
        int a; 
        cin >> a;
        sa[i] = a + sa[i - 1];
    }

    auto solve = [&](ll t) {
        if (t <= 0) return pi * R * R;
        if (t > sa[n]) t = sa[n];

        ld coeff = 2.0L * t * R + pi * R * R;
        int i = int(lower_bound(all(sa), t) - sa.begin() - 1);

        if (i >= 2)
            coeff -= (i - 1) * (1.0L - pi / 4) * R * R;

        if (i >= 1) {
            ld delta = min<ld>(R, t - sa[i]);
            coeff -= delta * R;
            ld h = R - delta;
            ld alpha = acosl(h / (ld)R);
            coeff += (alpha - 0.5L * sinl(2 * alpha)) * R * R / 2.0L;
        }

        return coeff;
    };

    while (q-- > 0) {
        ll l, r; 
        cin >> l >> r;
        cout << solve(r) - solve(l) << '\n';
    }
}