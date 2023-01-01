#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void solve() {
    // читаем вектор. надо найти его сумму, два минимума и два максимума
    int n; cin >> n;
    vector<int> a(n);
    for (auto &item : a)
        cin >> item;
    // сумма
    ll sum = accumulate(a.begin(), a.end(), 0LL);
    // минимумы и максимумы
    int min1 = INT_MAX, min2 = INT_MAX;
    int max1 = INT_MIN, max2 = INT_MIN;
    for (int i = 0; i < n; i++) {
        // обновляем минимумы:
        if (a[i] <= min1) {
            min2 = min1;
            min1 = a[i];
        } else if (a[i] <= min2) {
            min2 = a[i];
        }
        // обновляем максимумы:
        if (a[i] >= max1) {
            max2 = max1;
            max1 = a[i];
        } else if (a[i] >= max2) {
            max2 = a[i];
        }
    }
    // считаем ответы:
    for (int i = 0; i < n; i++) {
        ll res = sum - a[i]; // съедаем сами
        res -= (a[i] == min1 ? min2 : min1); // сестра ест минимум
        res -= (a[i] == max1 ? max2 : max1); // брат ест максимум
        cout << res << ' ';
    }
    cout << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt--) solve();
}