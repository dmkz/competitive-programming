#include <bits/stdc++.h>
#include <cassert>
using namespace std;
void solve() {
    // читаем данные:
    int n; cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    // будем вычитать из всех троек те тройки, которые не образуют треугольник
    // такие тройки лежат на одной прямой. переберём одну из точек треугольника
    // и посчитаем, сколько плохих троек она образует:
    int64_t answ = 0;
    for (int i = 0; i < n; i++) {
        map<pair<int,int>, int> cnt;
        for (int j = 0; j < n; j++) {
            if (j != i) {
                // вектор (xi, yi) -> (xj, yj):
                int dx = x[j] - x[i];
                int dy = y[j] - y[i];
                // нормализуем длину:
                int g = gcd(abs(dx), abs(dy));
                dx /= g, dy /= g;
                // нормализуем знак:
                if (dx < 0) dx = -dx, dy = -dy;
                if (dx == 0) dy = abs(dy);
                // добавляем в словарь:
                cnt[{dx, dy}]++;
            }
        }
        // теперь из всех способов выбрать 2 точки вычитаем те, которые лежат на одной прямой:
        int64_t curr = (n-1LL)*(n-2LL)/2;
        for (const auto &[_, k] : cnt)
            curr -= k * (k-1LL)/2;
        // обновляем глобальный ответ:
        answ += curr;
    }
    // выводим ответ, учитывая, что каждый треугольник посчитали трижды:
    assert(answ % 3 == 0);
    cout << answ / 3 << endl;
}
main() {
    int tt = 1; cin >> tt;
    while (tt --> 0) solve();
}