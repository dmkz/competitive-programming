#include <bits/stdc++.h>
using namespace std;
int main() {
    // читаем данные:
    int n, m, q; cin >> n >> m >> q;
    string s, t; cin >> s >> t;
    // генерируем массив a[i] = 1, если в позиции i есть вхождение t в s:
    vector<int> a(n);
    for (int i = 0; i + m - 1 < n; i++)
        if (s.substr(i, m) == t)
            a[i] = 1;
    // строим префикс-суммы:
    vector<int> pref_sum_a(n+1);
    for (int i = 0; i < n; i++)
        pref_sum_a[i+1] = pref_sum_a[i] + a[i];
    // отвечаем на запросы: каждый запрос за O(1);
    auto count = [&](int L, int R) {
        // так как длина подстроки равна m и подстрока не должна вылезать за R, то
        // подходят позиции: [L, L+1, L+2, ..., R - m + 1]
        R = R - m + 1;
        if (L > R) return 0; // нет ни одного вхождения
        return pref_sum_a[R+1] - pref_sum_a[L];
    };
    while (q --> 0) {
        int L, R; cin >> L >> R;
        L--, R--; // переход к 0-индексации
        cout << count(L, R) << '\n';
    }
}