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
    // Считаем длину блока одинаковых значений, начинающегося в каждой позиции.
    vector<int> blockLen(n);
    blockLen[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] == a[i + 1]) blockLen[i] = blockLen[i + 1] + 1;
        else blockLen[i] = 1;
    }
    // Выводим длины блоков.
    for (auto it : blockLen)
        cout << it << ' ';
    cout << '\n';
}