#include <bits/stdc++.h>
using namespace std;
void solve() {
    // это можно сделать только тогда, когда на чётных и нечётных позициях
    // все числа имеют одинаковую чётность.
    // cnt[чётность позиции][чётность числа] = кол-во чисел
    int cnt[2][2] = {};
    int n; cin >> n;
    for (int index = 0; index < n; index++) {
        int number; cin >> number;
        cnt[index % 2][number % 2]++;
    }
    // надо проверить, что на чётных и нечётных позициях полностью отсутствует
    // какая-либо одна чётность чисел (ноль чётных либо ноль нечётных чисел)
    bool ok =  (cnt[0][0] == 0 || cnt[0][1] == 0)
            && (cnt[1][0] == 0 || cnt[1][1] == 0);
    cout << (ok ? "YES\n" : "NO\n");
}
main() {
    int tt; cin >> tt;
    while (tt --> 0)
        solve();
}
