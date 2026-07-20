// Перед ответом на запросы для каждого префикса и каждого суффикса
// заранее посчитаем количество уникальных чисел. Для этого идём вдоль массива,
// вставляем очередной элемент в set и сохраняем размер set после вставки.
// При ответе на запросы берём из массива заранее посчитанные значения и выводим их.
#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем массив
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // считаем и запоминаем количество уникальных элементов на каждом префиксе:
    set<int> numbers;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        numbers.insert(a[i]);
        p[i] = numbers.size();
    }
    // аналогично для каждого суффикса:
    numbers.clear();
    vector<int> s(n);
    for (int i = n-1; i >= 0; i--) {
        numbers.insert(a[i]);
        s[i] = numbers.size();
    }
    // отвечаем на запросы:
    while (q --> 0) {
        char c; int i;
        cin >> c >> i;
        i--;
        cout << (c == 'p' ? p[i] : s[i]) << '\n';
    }
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
