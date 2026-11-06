#include <bits/stdc++.h>
#include <bits/extc++.h>
using ll = long long;
#define int ll
using namespace std;
using vpii = vector<pair<int,int>>;
// факторизация на простые сомножители:
vpii factor(int m) {
    vpii answ;
    for (int x = 2; x * x <= m; x++)
        if (m % x == 0) {
            int p = 1;
            m /= x;
            while (m % x == 0) m /= x, p++;
            answ.emplace_back(x, p);
        }
    if (m > 1) answ.emplace_back(m, 1);
    return answ;
}
// сколько раз n! делится на p:
int getPowInFact(int n, int p) {
    return (n < p ? 0 : (n / p + getPowInFact(n / p, p)));
}
// решение задачи:
void solve() {
    // читаем данные:
    int l, m; cin >> l >> m;
    // раскладываем m на простые множители:
    auto divs = factor(m);
    // функция проверки, подходит ли граница r?
    auto check = [&](int r) {
        // проверить, что произведение чисел l, l+1, ..., r делится на m
        // это отношение двух факториалов fact(r) / fact(l-1)
        // нужно посчитать, сколько раз каждый из факториалов делится на простое число p
        for (const auto &[p, k] : divs) {
            int t = getPowInFact(r, p) - getPowInFact(l-1, p);
            if (t < k) return false;
        }
        return true;
    };
    // находим первое подходящее r бинарным поиском на отрезке [l, l+m+1):
    int low = l-1, high = l+m;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (check(mid)) high = mid;
        else low = mid;
    }
    cout << high << "\n";
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
    return 0;
}
