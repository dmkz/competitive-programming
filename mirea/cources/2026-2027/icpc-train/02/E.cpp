#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using ll = long long;
string ask(ll x) {
    cout << "? " << x << endl;
    string res; cin >> res;
    return res;
}
void solve() {
    ll n; cin >> n;
    // сначала находим L:
    ll low = 0, high = n+1;
    while (high - low > 1) {
        ll mid = (low + high) / 2;
        if (ask(mid) == "LEFT") low = mid;
        else high = mid;
    }
    ll L = high;
    // теперь находим R:
    high = n+1;
    while (high - low > 1) {
        ll mid = (low + high) / 2;
        if (ask(mid) == "RIGHT") high = mid;
        else low = mid;
    }
    ll R = low;
    // выводим ответ
    cout << "! " << L << " " << R << endl;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int tt = 1; cin >> tt;
    while (tt --> 0) solve();
    return 0;
}
