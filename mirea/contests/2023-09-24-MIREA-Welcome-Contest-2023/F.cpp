#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(9);
    int tt; cin >> tt;
    while (tt --> 0) {
        int n; cin >> n;
        vector<int> x(n), y(n);
        for (int i = 0; i < n; i++)
            cin >> x[i] >> y[i];
        // считаем префикс-суммы для площадей трапеций:
        vector<ll> s(n);
        for (int i = 1; i < n; i++)
            s[i] = s[i-1] + (y[i-1] + y[i]) * 1LL * (x[i] - x[i-1]);
        // функция для подсчёта суммы площадей от x[0] до R:
        // ответ на отрезке L .. R это solve(L, R) = solve(0, R) - solve(0, L)
        auto solve = [&](int R) {
            // бинпоиском находим в какой отрезок ломаной попадает точка
            int up = int(upper_bound(x.begin(), x.end(), R) - x.begin());
            int i = up - 1;
            assert(i >= 0);
            // точка попадает в отрезок [x[i], x[i+1]]
            ld res = s[i];
            if (x[i] == R)
                return res;
            // иначе надо считать площадь при частичном попадании
            int dx = R - x[i];
            // находим ответ через подобие
            // (yr - y[i]) / (y[i+1] - y[i]) == (R - x[i]) / (x[i+1] - x[i])
            ld A = ld(R - x[i]) / (x[i+1] - x[i]);
            ld yr = A * (y[i+1] - y[i]) + y[i];
            res += (y[i] + yr) * dx;
            return res;
        };
        // отвечаем на запросы
        int q; cin >> q;
        while (q --> 0) {
            int L, R; cin >> L >> R;
            cout << solve(R) - solve(L) << endl;
        }
    }
}