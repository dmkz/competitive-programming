#include <bits/stdc++.h>
#include <bits/extc++.h>
using ll = long long;
using ld = long double;
using namespace std;
int ask(ll a) {
    cout << "? " << a << endl;
    int res = 0;
    cin >> res;
    return res;
}
// основной принцип решения: существует такое значение a, которое поделит отрезок из кандидатов
// на ответ на примерно равные половины. Изначально у нас подходят x = 0, 1, 2, ..., m-1
// то есть весь отрезок [L, R], где L=0, R=m-1
// спросив a=1, мы получим, что мы поделим наш отрезок на две части, например при m = 10:
//      0 1 2 3 4 5 6 7 8 9
// a=1: + + + + + - - - - -
// один запрос возвращает, меньше ли остаток от деления (a * x) чем m/2
// далее, в зависимости от ответа, мы продолжаем рекурсивно в одном из двух отрезков: [0, 4] либо [5, 9]
// перебор всех случаев показывает, что такое a:
// 1. всегда существует
// 2. оно равно какой-то степени двойки {1, 2, 4, 8, ...}
// ----------- ПОЛНЫЙ ПЕРЕБОР И ПРОВЕРКА ОТВЕТА: ---------------------
ll f(ll a, ll x, ll m) {
    ll y = (ll)(__int128(a) * x % m);
    return (2 * y < m ? 0 : 1);
}
struct Segment {
    ll val{}, L{}, R{};
    string to_string() const {
        string res = "[" + std::to_string(L) + ".." + std::to_string(R) + ": " + std::to_string(val) + "]";
        return res;
    }
};
vector<Segment> split(ll a, ll L, ll R, ll m) {
    vector<Segment> segments; // {val, L, R}
    for (ll x = L; x <= R; x++) {
        ll res = f(a, x, m);
        if (segments.empty() || segments.back().val != res)
            segments.emplace_back(res, x, x);
        segments.back().R = x;
    }
    return segments;
}
ll findA(ll L, ll R, ll m) {
    // найти значение a, которое поделит пополам на примерно равные части
    for (ll a = 1; a < m; a *= 2) {
        auto segments = split(a, L, R, m);
        if (segments.size() == 2) {
            const auto [v0, L0, R0] = segments[0];
            const auto [v1, L1, R1] = segments[1];
            ll len0 = R0 - L0 + 1;
            ll len1 = R1 - L1 + 1;
            if (abs(len0-len1) <= 1)
                return a;
        }
    }
    return -1;
}
void research() {
    for (ll m = 2; m <= 10; m++) {
        function<void(ll L, ll R)> dfs = [&](ll L, ll R) {
            if (L == R) return;
            ll a = findA(L, R, m);
            cout << "segment [" << L << ".." << R << "]: " << a << endl;
            auto segs = split(a, L, R, m);
            assert(segs.size() == 2u);
            for (const auto &[_, l, r] : segs)
                dfs(l, r);
        };
        ll L = 0, R = m-1;
        cout << "m = " << m << ":\n";
        dfs(L, R);
    }
    exit(0);
}
// ------------ РЕШЕНИЕ ЗАДАЧИ ------------
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
    //research();
    cin.tie(0)->sync_with_stdio(0);
    int tt = 1; cin >> tt;
    while (tt --> 0) solve();
    return 0;
}
