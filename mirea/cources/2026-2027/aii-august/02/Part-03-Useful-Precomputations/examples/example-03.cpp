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
    // Считаем длину строго возрастающего подотрезка из каждой позиции.
    vector<int> incLen(n);
    incLen[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] < a[i + 1]) incLen[i] = incLen[i + 1] + 1;
        else incLen[i] = 1;
    }
    // Выводим длины возрастающих подотрезков.
    for (auto it : incLen)
        cout << it << ' ';
    cout << '\n';
}