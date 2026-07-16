#include <bits/stdc++.h>
using namespace std;
const int inf = 1000000007;
void solve() {
    // храним границы свободных отрезков в виде пар (R, L) - сначала правая граница,
    // затем левая граница. Это удобно, потому что s.lower_bound({x,-inf}) найдёт нам
    // первый отрезок такой, что: x <= R.
    // Дополнительно храним мультисет из длин отрезков, чтобы выдавать максимум.
    int n, q; cin >> n >> q;
    set<pair<int,int>> segments{{n, 1}}; // 1 отрезок: [1, n]
    multiset<int> lengths = {n, 0};      // 2 элемента: "n" и "0"
    while (q --> 0) {
        char c; int l, r;
        cin >> c >> l >> r;
        // находим отрезок, в который попадает граница r:
        auto iter = segments.lower_bound({r, -inf});
        // запоминаем его левую и правую границу, затем удаляем вместе с длиной:
        auto [R, L] = *iter;
        segments.erase(iter);
        lengths.erase(lengths.find(R-L+1));
        // Из отрезка [L, R] мы вырезали подотрезок [l, r]. Нужно вставить два
        // два отрезка: [L, l-1] и [r+1, R]:
        if (L < l) {
            segments.insert({l-1, L});
            lengths.insert(l - L);
        }
        if (r < R) {
            segments.insert({R, r+1});
            lengths.insert(R - r);
        }
        // выводим ответ - максимальную длину отрезка:
        cout << *lengths.rbegin() << '\n';
    }
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
