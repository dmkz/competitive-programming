#include <bits/stdc++.h>
using namespace std;
using ld = long double;
bool check(const auto& a, int64_t m, ld x) {
    int64_t pieces = 0;
    for (auto it : a) {
        ld count = it / x;
        if (count >= m - pieces) return true;
        pieces += (int64_t)count;
    }
    return false;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Ищем наибольшую длину, из которой получится хотя бы m отрезков.
    int n; int64_t m; cin >> n >> m;
    vector<int64_t> a(n);
    for (auto& it : a) cin >> it;
    ld low = 0, high = *max_element(a.begin(), a.end()) + 1;
    for (int iter = 0; iter < 100; iter++) {
        ld mid = (low + high) / 2;
        if (check(a, m, mid)) low = mid;
        else high = mid;
    }
    cout << fixed << setprecision(10) << low << '\n';
}