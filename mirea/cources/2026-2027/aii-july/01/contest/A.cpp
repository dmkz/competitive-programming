// Сначала найдём максимум в исходном массиве. Назовём его max1. Теперь найдём второй
// максимум, пройдя вдоль массива ещё раз в поисках максимального элемента среди тех,
// которые меньше max1.

#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем массив:
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // первый максимум:
    const int max1 = *max_element(a.begin(), a.end());
    // второй максимум:
    int max2 = -1000000000;
    for (int i = 0; i < n; i++)
        if (max2 < a[i] && a[i] < max1)
            max2 = a[i];
    cout << max2 << endl;
}
int main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
