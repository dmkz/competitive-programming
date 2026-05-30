#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем:
    int n; cin >> n;
    vector<int> q(n+1);
    for (int i = 1, j; i <= n; i++) {
        cin >> j;
        q[j] = i;
    }
    for (int j = 1; j <= n; j++)
        cout << q[j] << ' ';
}