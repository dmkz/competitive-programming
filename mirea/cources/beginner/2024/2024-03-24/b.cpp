#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
void solve() {
    // посчитаем m = количество уникальных элементов
    // тогда дубликатов n - m. Вы их уничтожаем по два
    // за (n-m)/2 операций. В зависимости от остатка,
    // остаётся 1 дубликат либо 0 дубликатов
    // тогда придётся выкинуть один дубликат вместе с оригиналом
    int n; cin >> n;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    sort(all(a));
    a.erase(unique(all(a)), a.end());
    int m = (int)a.size();
    int nOps = (n - m + 1) / 2;
    cout << n - nOps * 2 << endl;
}
int main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
