#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    for (int i = 0; i < n; i++) {
        int k; cin >> k;
        string s; cin >> s;
        // посчитаем, на сколько изменился элемент в итоге
        int delta = 0;
        for (auto it : s) {
            if (it == 'U')
                delta++;
            else
                delta--;
        }
        // вычтем изменение. тогда получим
        // оригинальный элемент
        a[i] -= delta;
        // возьмём остаток от деления на 10
        a[i] %= 10;
        if (a[i] < 0)
            a[i] += 10;
    }
    // выводим ответ
    for (auto it : a)
        cout << it << ' ';
    cout << '\n';
}
int main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
