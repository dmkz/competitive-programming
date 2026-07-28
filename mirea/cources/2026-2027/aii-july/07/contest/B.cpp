// Чтобы набрать как можно больше товаров, нужно покупать самые дешёвые из них. Поэтому
// отсортируем пары (значение, индекс) в порядке возрастания значения и пройдём по ним,
// набирая товары до тех пор, пока не закончатся деньги. Запоминаем индексы купленных товаров.
#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем элементы и сортируем пары (значение, индекс):
    int n; int64_t s;
    cin >> n >> s;
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i+1;
    }
    // сортируем пары лексикографически:
    sort(a.begin(), a.end());
    // формируем ответ: берём самые дешёвые товары, пока не кончились деньги
    vector<int> answ;
    for (const auto &[ai, i] : a)
        if (s >= ai) {
            s -= ai;
            answ.push_back(i);
        }
    // выводим ответ:
    cout << answ.size() << '\n';
    for (auto it : answ)
        cout << it << ' ';
    cout << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
