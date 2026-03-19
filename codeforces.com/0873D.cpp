// разделяй и властвуй, конструктив, сортировка слиянием
#include <bits/stdc++.h>
using namespace std;
void solve(auto &a, int l, int r, int &k) {
    if (l + 1 == r || k <= 0)
        return;
    int m = (l+r)/2;
    reverse(a.begin()+l, a.begin()+r);
    reverse(a.begin()+l, a.begin()+m);
    reverse(a.begin()+m, a.begin()+r);
    k -= 2;
    solve(a, l, m, k);
    solve(a, m, r, k);
}
auto solve(int n, int k) {
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        a[i] = i+1;
    k--;
    solve(a, 0, n, k);
    if (k != 0)
        a = {-1};
    return a;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    for (auto it : solve(n, k))
        cout << it << ' ';
    cout << '\n';
}
