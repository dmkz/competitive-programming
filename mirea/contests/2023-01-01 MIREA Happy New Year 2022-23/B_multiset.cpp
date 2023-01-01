#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void solve() {
    // читаем вектор. надо найти его сумму.
    // элементы будем хранить также в мультисете, чтобы знать минимум и максимум всегда
    int n; cin >> n;
    multiset<int> ms;
    vector<int> a(n);
    ll sum = 0;
    for (auto &item : a) {
        cin >> item;
        ms.insert(item);
        sum += item;
    }
    // считаем ответы:
    for (int i = 0; i < n; i++) {
        // временно удаляем текущий элемент из мультимножества:
        ms.erase(ms.find(a[i]));
        ll res = sum - a[i]; // съедаем сами
        res -= *ms.begin(); // сестра ест минимум
        res -= *ms.rbegin(); // брат ест максимум
        cout << res << ' ';
        // возвращаем текущий элемент обратно в множество:
        ms.insert(a[i]);
    }
    cout << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt--) solve();
}