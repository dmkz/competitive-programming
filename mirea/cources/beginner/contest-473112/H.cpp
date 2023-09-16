#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using ll = long long;
using vl = vector<ll>;
int main() {
    // предподсчёт всех степеней, которые не являются квадратами
    // квадраты будем считать отдельно
    vl powers;
    for (ll a = 2; a <= (ll)1e6; a++)
        for (ll curr = a * a; curr <= (ll)1e18L / a; ) {
            curr *= a;
            // вставляем только если не полный квадрат
            if (ll root = (ll)sqrtl(curr); root * root != curr)
                powers.push_back(curr);
        }
    // сортируем и удаляем повторы
    sort(all(powers));
    powers.erase(unique(all(powers)), powers.end());
    // отвечаем на запросы
    auto countPowers = [&](ll R) {
        // количество степеней на отрезке [0, R]
        ll res = upper_bound(all(powers), R) - powers.begin();
        res += (ll)sqrtl(R);
        return res;
    };
    int q; cin >> q;
    while (q --> 0) {
        ll L, R; cin >> L >> R;
        cout << (countPowers(R) - countPowers(L-1)) << endl;
    }
}
