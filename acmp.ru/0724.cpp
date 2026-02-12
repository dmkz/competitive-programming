// перебор, битмаски, O(m * 2^m)
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
using vi = vector<int>;
using pii = pair<int,int>;
main() {
    int n, m; cin >> n >> m;
    vi a(m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            a[j] |= ((1-x) << i);
        }
    pii best(INT_MAX, 0);
    for (int subset = 1; subset < (1 << m); subset++) {
        int total = 0, sz = 0;
        for (int i = 0; i < m; i++)
            if ((subset >> i) & 1) {
                total |= a[i];
                sz++;
            }
        if (total == ((1 << n) - 1))
            best = min(best, pii(sz, subset));
    }
    if (best.first <= m) {
        cout << best.first << "\n";
        for (int i = 0; i < m; i++)
            if ((best.second >> i) & 1)
                cout << i+1 << ' ';
        cout << '\n';
    } else
        cout << "Impossible\n";
}
