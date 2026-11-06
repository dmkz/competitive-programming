#include <bits/stdc++.h>
#include <bits/extc++.h>
using ll = long long;
using ld = long double;
using namespace std;
// основной принцип решения: существует такое значение a, которое поделит отрезок из кандидатов
// на ответ на примерно равные половины. Изначально у нас подходят x = 0, 1, 2, ..., m-1
// то есть весь отрезок [L, R], где L=0, R=m-1
// спросив a=1, мы получим, что мы поделим наш отрезок на две части, например при m = 10:
//      0 1 2 3 4 5 6 7 8 9
// a=1: + + + + + - - - - -
// один запрос позволяет определить, меньше ли остаток от деления (a * x) чем m/2
// далее, в зависимости от ответа, мы продолжаем рекурсивно в одном из двух отрезков: [0, 4] либо [5, 9]
// перебор (файл E-research.cpp) всех случаев показывает, что такое a:
// 1. всегда существует
// 2. оно равно какой-то степени двойки {1, 2, 4, 8, ...}
// 3. оно равно глубине рекурсии dfs разделения отрезка
// ------------ РЕШЕНИЕ ЗАДАЧИ ------------
int ask(ll a) {
    cout << "? " << a << endl;
    int res = 0;
    cin >> res;
    return res;
}
ll f(ll a, ll x, ll m) {
// жюри возвращает значение f(a, x, m)
    ll y = (ll)(__int128(a) * x % m);
    return (2 * y < m ? 0 : 1);
}
void solve() {
    ll m; cin >> m;
    function<ll(ll,ll,ll)> dfs = [&](ll L, ll R, ll a) {
        if (L == R) return L;
        // находим границу, в которой меняется ответ:
        ll low = L, high = R;
        while (high - low > 1) {
            ll mid = (low + high) / 2;
            if (f(a, mid, m) == f(a, L, m)) low = mid;
            else high = mid;
        }
        if (ll val = ask(a); val == f(a, L, m))
            return dfs(L, low, a*2);
        else
            return dfs(high,R,a*2);
    };
    ll x = dfs(0, m-1, 1);
    cout << "! " << x << endl;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int tt = 1; cin >> tt;
    while (tt --> 0) solve();
    return 0;
}
