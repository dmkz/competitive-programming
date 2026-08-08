#include <bits/stdc++.h>
using namespace std;
using ll = long long;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Читаем массив:
    int n; cin >> n;
    vector<ll> a(n);
    for (auto& it : a)
        cin >> it;
    // Ищем первую позицию справа с отличающимся значением.
    vector<int> firstDifferent(n);
    firstDifferent[n - 1] = n;
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] == a[i + 1]) {
            firstDifferent[i] = firstDifferent[i + 1];
        } else {
            firstDifferent[i] = i + 1;
        }
    }
    // Выводим позиции в нумерации с единицы.
    for (auto it : firstDifferent)
        cout << it + 1 << ' ';
    cout << '\n';
}