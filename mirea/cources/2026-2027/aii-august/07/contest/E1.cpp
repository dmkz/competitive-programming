#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n; cin >> n;
    map<int,int> cnt;
    int answ = 0, nZeros = 0;
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        if (a < 0)
            a = -a;
        // Ноль можно поставить в пару с любым числом:
        if (a == 0) {
            nZeros++;
            answ += i;
            continue;
        }
        // Факторизуем число, выкидывая все квадраты простых:
        int x = 1;
        for (int p = 2; p * p <= a; p++)
            if (a % p == 0) {
                int odd = 0;
                while (a % p == 0) {
                    a /= p;
                    odd = 1 - odd;
                }
                if (odd) x *= p;
            }
        if (a > 1)
            x *= a;
        // Теперь остались только простые, которые входят нечётное количество раз
        // Чтобы получить полный квадрат, мы должны поставить в пару с таким же элементом:
        answ += cnt[x]++;
        answ += nZeros; // с нулями тоже можно
    }
    cout << answ << '\n';
}
main() {
    int tt = 1; cin >> tt;
    while (tt --> 0) solve();
}
