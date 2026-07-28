// Рекурсивно перебираем все варианты разбиения людей на команды. Рассматриваем два варианта:
// 1. Включаем i-го человека в первую команду;
// 2. Включаем i-го человека во вторую команду.
// Храним набранную разницу между силами двух команд. Ответ - модуль этой разности.
#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем данные
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // запускаем поиск решения:
    int64_t diff = 0, answ = 1e18L;
    function<void(int,int,int)> dfs = [&](int i, int n1, int n2){
        if (i == n) {
            if (n1 == k)
                answ = min(answ, abs(diff));
            return;
        }
        // включаем i-го человека в первую команду:
        if (n1 < k) {
            diff += a[i];
            dfs(i+1, n1+1, n2);
            diff -= a[i];
        }
        // включаем i-го человека во вторую команду:
        if (n2 < n - k) {
            diff -= a[i];
            dfs(i+1, n1, n2+1);
            diff += a[i];
        }
    };
    dfs(0, 0, 0);
    cout << answ << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
