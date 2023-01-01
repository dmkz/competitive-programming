#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем паровозики как вектор из векторов:
    int n; cin >> n;
    vector a(n, vector<int>());
    for (auto &vec : a) {
        int k; cin >> k;
        vec.resize(k);
        for (auto &item : vec)
            cin >> item;
    }
    // сортируем паровозики лексикографически:
    sort(a.begin(), a.end());
    // выводим паровозики на экран:
    for (auto &vec : a) {
        cout << vec.size();
        for (auto &item : vec)
            cout << ' ' << item;
        cout << '\n';
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt--) solve();
}