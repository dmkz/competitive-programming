#include <bits/stdc++.h>
using namespace std;
void solve() {
    // храним свободные отрезки в map<int, int>: ключ - левая граница L,
    // значение - правая граница R. Тогда upper_bound(l) найдёт первый
    // отрезок, который начинается строго правее l, а предыдущий отрезок
    // и будет тем самым [L, R], который содержит запрос [l, r].
    // Дополнительно храним мультисет из длин отрезков, чтобы выдавать максимум.
    int n, q; cin >> n >> q;
    map<int, int> segments{{1, n}}; // 1 отрезок: [1, n]
    multiset<int> lengths = {n, 0}; // 2 элемента: "n" и "0"
    while (q --> 0) {
        char c; int l, r;
        cin >> c >> l >> r;
        // находим отрезок, в который попадает граница l:
        auto iter = prev(segments.upper_bound(l));
        // запоминаем его левую и правую границу, затем удаляем вместе с длиной:
        auto [L, R] = *iter;
        segments.erase(iter);
        lengths.erase(lengths.find(R-L+1));
        // Из отрезка [L, R] мы вырезали подотрезок [l, r]. Нужно вставить два
        // отрезка: [L, l-1] и [r+1, R]:
        if (L < l) {
            segments[L] = l-1;
            lengths.insert(l - L);
        }
        if (r < R) {
            segments[r+1] = R;
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
