// Нужно посчитать количество пар: a[i] + a[j] <= s. Для этого зафиксируем a[j] и
// перенесём направо. Тогда требуется посчитать количество элементов a[i]:
// a[i] <= (s - a[j]) на полуинтервале [0, j) для каждого a[j].

#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем данные (сразу в 64-битный тип, чтобы не переполниться)
    int64_t n, s;
    cin >> n >> s;
    vector<int64_t> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end());
    int64_t answ = 0;
    for (int j = 0; j < n; j++)
        answ += int(upper_bound(a.begin(), a.begin() + j, s - a[j]) - a.begin());
    cout << answ << '\n';
}
int main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
    return 0;
}
