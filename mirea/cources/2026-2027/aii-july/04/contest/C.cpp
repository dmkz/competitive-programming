// Сначала построим префиксные суммы s поверх массива a. Тогда сумма на отрезке
// [l, r] равна s[r] - s[l-1]. Нужно найти такое r (r >= l), для которого
// s[r] - s[l-1] >= x. Переносим всё, что знаем, направо и получаем: s[r] >= x + s[l-1].
// Так как элементы массива неотрицательны, массив s монотонно не убывает,
// следовательно, можно применить бинарный поиск.
// Для решения задачи достаточно вызвать lower_bound для x + s[l-1], начиная с l.
#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем массив
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // считаем префикс-суммы:
    vector<int64_t> s(n+1);
    for (int i = 0; i < n; i++)
        s[i+1] = s[i] + a[i];
    // отвечаем на запросы:
    while (q --> 0) {
        int l; int64_t x;
        cin >> l >> x;
        // s[r] - s[l-1] >= x ==> s[r] >= x + s[l-1]
        auto iter = lower_bound(s.begin()+l, s.end(), x + s[l-1]);
        cout << int(iter - s.begin()) << '\n';
    }
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
