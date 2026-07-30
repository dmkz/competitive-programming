// Будем поддерживать префиксные суммы для площадей коробок. Они позволяют добавлять
// новую коробку в конец, удалять коробку с конца, а также считать сумму на любом подотрезке,
// в том числе и на суффиксе длины k.
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
void solve() {
    // читаем данные и считаем префиксные суммы: i-й элемент вектора будет равен
    // сумме площадей всех коробок с номерами от 0 до i-1.
    int n, q; cin >> n >> q;
    vector<int64_t> s = {0};
    for (int i = 0; i < n; i++) {
        int wi, hi; cin >> wi >> hi;
        s.push_back(s.back() + wi * 1LL * hi);
    }
    // обрабатываем запросы:
    while (q --> 0) {
        char t; cin >> t;
        if (t == '?') {
            // считаем сумму на отрезке через префиксные суммы:
            int k; cin >> k;
            cout << s.back() - s[s.size() - 1 - k] << '\n';
        } else if (t == '+') {
            // добавляем новый элемент в конец, пересчитывая префиксные суммы:
            int wi, hi; cin >> wi >> hi;
            s.push_back(s.back() + wi * 1LL * hi);
        } else {
            // удаляем самый крайний элемент:
            assert(t == '-');
            s.pop_back();
        }
    }
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
