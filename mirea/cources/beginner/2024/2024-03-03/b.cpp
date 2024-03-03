#include <bits/stdc++.h>
using namespace std;
const int inf = (int)1e9+7;
void solve() {
    int n, q; cin >> n >> q;
    // нужно прочитать все конфеты, отсортировать их по убыванию, найти
    // префикс-суммы и сделать бинарный поиск по префикс-суммам
    // читаем:
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // сортируем:
    sort(a.begin(), a.end(), greater<>());
    // считаем сумму на префиксе:
    for (int i = 1; i < n; i++)
        a[i] += a[i-1];
    // отвечаем на запросы:
    while (q --> 0) {
        int x; cin >> x;
        // сначала проверка на то, что мы вообще можем такое набрать:
        if (a.back() < x) {
            cout << "-1\n";
            continue;
        }
        // теперь мы точно знаем, что сможем, поэтому ищем ответ:
        auto nearestNotLessThanX = lower_bound(a.begin(), a.end(), x);
        int position = int(nearestNotLessThanX - a.begin());
        cout << position+1 << "\n";
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
