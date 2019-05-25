/*
    Задача: 921. Турнир - 2
    
    Решение: теория вероятностей, тернарный поиск, математическое ожидание, O(log(k))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
int main() {
    ll k; int a, b, c;
    while (std::cin >> k >> a >> b >> c) {
/*
    Всего k матчей. Пусть шахматных x.
    Математическое ожидание количества очков, набранных первой командой:
        x * (p1 + 0.5 * p2) + q1 * (k - x)
    Математическое ожидание количества очков, набранных второй командой:
        x * (p3 + 0.5 * p2) + q2 * (k - x)
    Разница:
        x * (p1 - p3) + (q1 - q2) * (k - x)
        x * (p1 - p3 + q2 - q1) + (q1 - q2) * k
    Подставляем значения:
        p1 = a
        p3 = 100 - a - c
        q2 = b
        q1 = 100 - b
    Получаем:
        x * (2 * a + c + 2 * b - 200) + (100 - 2 * b) * k
*/  
        auto f = [&](ll x) {
            return std::abs(x * (2 * a + c + 2 * b - 200) + (100 - 2 * b) * k);
        };
        auto naive = [&](ll fi, ll se) {
            ll md = (ll)1e18L;
            ll mx = k;
            for (ll x = fi; x <= se; ++x) {
                if (f(x) < md) { mx = x; md = f(x); }
            }
            return mx;
        };
        
        auto fast = [&]() {
            ll low = 1, high = k - 1;
            while (high - low > 10) {
                ll x1 = (low + high) / 2;
                ll x2 = x1 + 1;
                ll y1 = f(x1);
                ll y2 = f(x2);
                if (y1 <= y2) {
                    high = x2;
                } else {
                    low = x1;
                }
            }
            return naive(low, high);
        };
        std::cout << fast() << std::endl;
    }
    return 0;
}