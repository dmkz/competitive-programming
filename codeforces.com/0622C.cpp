// динамическое программирование, запросы на отрезках
#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем массив
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // считаем для каждого элемента позицию ближайшего справа элемента,
    // который не совпадает с ним по значению
    vector<int> nextNotEqual(n, n);
    for (int i = n-2; i >= 0; i--)
        nextNotEqual[i] = (a[i] == a[i+1] ? nextNotEqual[i+1] : i+1);
    // отвечаем на запросы:
    while (m --> 0) {
        int l, r, x; cin >> l >> r >> x;
        l--, r--;
        if (a[l] != x) {
            cout << l+1 << '\n';
        } else {
            int p = nextNotEqual[l];
            if (p <= r)
                cout << p+1 << '\n';
            else
                cout << -1 << '\n';
        }
    }
}
