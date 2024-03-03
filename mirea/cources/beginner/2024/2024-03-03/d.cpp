#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // нужно знать максимальную ступеньку на префиксе
    // если мы не преодолеем максимум, то не преодолеем и остальные элементы
    // считаем максимальные ступеньки:
    vector<int> prefMax = a;
    for (int i = 1; i < n; i++)
        prefMax[i] = max(a[i], prefMax[i-1]);
    // также нужно знать сумму ступенек на префиксе, чтобы сообщать ответ
    vector<ll> sum(1+n); // sum[i] = сумма ступенек до i-й
    for (int i = 0; i < n; i++)
        sum[i+1] = sum[i] + a[i];
    // отвечаем на запросы:
    while (q --> 0) {
        int k; cin >> k;
        auto nearestGreater = upper_bound(prefMax.begin(), prefMax.end(), k);
        int position = int(nearestGreater - prefMax.begin());
        cout << sum[position] << " ";
    }
    cout << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
