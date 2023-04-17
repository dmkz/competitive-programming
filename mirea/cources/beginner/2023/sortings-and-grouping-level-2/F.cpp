#include <bits/stdc++.h>
using namespace std;
int divs(int x) {
    int answ{};
    for (int i = 1; i * i <= x; i++)
        if (int j = x / i; j * i == x)
            answ += 1 + (j != i);
    return answ;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        // создаём пары (число делителей x, само число x):
        // да, посчитаем число делителей для каждого x один раз
        // можно было сортировать по числу делителей, вызывая функцию divs в
        // компараторе, но это увеличение асимптотики в логарифм раз и TLE
        int n; cin >> n;
        vector<pair<int,int>> a(n);
        for (auto &[d,x] : a)
            cin >> x, d = divs(x);
        // сортируем по возрастанию:
        sort(a.begin(),a.end());
        // выводим ответ:
        for (auto [_,x] : a)
            cout << x << ' ';
        cout << '\n';
    }
}