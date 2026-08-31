#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = double;
struct Pt {
    ll x, y;
    Pt operator-(const Pt &p) const {
        return {x - p.x, y - p.y};
    }
};
ll dot(Pt a, Pt b) {
    return a.x * b.x + a.y * b.y;
}
ll cross(Pt a, Pt b) {
    return a.x * b.y - a.y * b.x;
}
ld angle(Pt a, Pt b) {
    return atan2(abs(cross(a,b)),dot(a,b));
}
void solve() {
    int n; cin >> n;
    vector<int> x(n+2), y(n+2);
    for (auto &it : x) cin >> it;
    for (auto &it : y) cin >> it;
    Pt O = {x[n+1], y[n+1]};
    ld sum = 0;
    for (int i = 1; i <= n; i++) {
        Pt A = {x[i-1], y[i-1]};
        Pt B = {x[i], y[i]};
        sum += angle(B - O, A - O);
    }
    cout << fixed << setprecision(12) << sum << '\n';
}
main() {
    int tt = 1; cin >> tt;
    while (tt --> 0) solve();
}