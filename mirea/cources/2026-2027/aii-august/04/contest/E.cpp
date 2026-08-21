#include <bits/stdc++.h>
#include <cassert>
using namespace std;
const int mod = (int)1e9+7;
// быстрое возведение в степень:
int binpow(int a, int64_t n) {
    int r = 1;
    while (n > 0) {
        if (n % 2 == 1)
            r = int(r * 1LL * a % mod);
        a = int(a * 1LL * a % mod);
        n >>= 1;
    }
    return r;
}
// решение:
void solve() {
    int n, m; cin >> n >> m;
    int q; cin >> q;
    int invPow2 = binpow(binpow(2, 60), mod-2);
    int answ = binpow(2, 60LL * n * m);
    int64_t xorRows = 0, xorCols = 0;
    int usedRows = 0, usedCols = 0;
    while (q --> 0) {
        char ch; cin >> ch;
        if (ch == 'r') {
            int k; int64_t x;
            cin >> k >> x;
            usedRows++;
            xorRows ^= x;
        } else {
            assert(ch == 'c');
            int k; int64_t x;
            cin >> k >> x;
            usedCols++;
            xorCols ^= x;
        }
        if (usedRows == n && usedCols == m && xorRows != xorCols)
            answ = 0;
        if (usedRows + usedCols < n + m)
            answ = int((answ * 1LL * invPow2) % mod);
        cout << answ << '\n';
    }
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
