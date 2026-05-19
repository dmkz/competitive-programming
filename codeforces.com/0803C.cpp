// делители, факторизация, жадные алгоритмы
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n, k;
    cin >> n >> k;
    ll answer = 0;
    auto update = [&](ll g) {
        // проверяем, можно ли разложить:
        // g * (1 + 2 + 3 + ...) = n
        auto limit = k * (k+1.0L)/2;
        if (limit <= n / g)
            answer = max(answer, g);
    };
    for (int i = 1; i * 1LL * i <= n; i++)
        if (n % i == 0) {
            update(i);
            update(n / i);
        }
    if (answer > 0) {
        // восстанавливаем ответ:
        vector<ll> a(k);
        iota(all(a), 1);
        a[k-1] = n / answer - std::accumulate(all(a)-1, ll(0));
        for (auto &it : a) {
            it *= answer;
            cout << it << ' ';
        }
        cout << '\n';
    } else {
        cout << "-1\n";
    }
}