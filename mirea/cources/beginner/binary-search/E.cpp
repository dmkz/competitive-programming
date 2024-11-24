#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto &it : a)
            cin >> it;
        // если перевернуть, то a[i] = количество чисел, > i
        // если это верно, то yes, иначе no
        auto b = a;
        sort(b.begin(), b.end());
        bool ok = 1;
        for (int i = 0; i < n; i++) {
            int gt = b.end() - upper_bound(b.begin(), b.end(), i);
            ok &= (a[i] == gt);
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }
}
