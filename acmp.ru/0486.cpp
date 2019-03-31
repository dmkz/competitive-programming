/*
    Задача: 486. Рыбаки - 2
    
    Решение: математическое моделирование, O(log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
typedef long long ll;
ll pow(ll a, ll n) {
    ll ret = 1;
    while (n > 0) {
        if (n & 1) { ret *= a; }
        n >>= 1; a *= a;
    }
    return ret;
}
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    ll n, k;
    while (std::cin >> n >> k) {
        if (n == 2) {
            for (ll sum1 = 1; ;sum1++) {
                ll rem1 = sum1 % n;
                if (rem1 != k) {
                    continue;
                }
                ll sum2 = sum1 - sum1 / n - k;
                ll rem2 = sum2 % n;
                if (rem2 != k || sum2 / n == 0) {
                    continue;
                }
                std::cout << sum1 << std::endl;
                break;
            }
        } else {
            std::cout << (ll)pow(n, n) - (n-1) * k << std::endl;
        }
    }
    return 0;
}