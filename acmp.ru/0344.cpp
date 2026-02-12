// сортировка, ближайшие точки на прямой
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using pii = pair<int, int>;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<pii> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i+1;
    }
    sort(all(a));
    pii best(INT_MAX, -1);
    for (int i = 0; i + 1 < n; i++) {
        pii curr{a[i+1].first - a[i].first, i};
        best = min(best, curr);
    }
    auto [d, i] = best;
    cout << d << "\n";
    cout << a[i].second << ' ' << a[i+1].second << "\n";
}
