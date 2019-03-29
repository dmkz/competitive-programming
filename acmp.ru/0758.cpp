/*
    Задача: 758. Веревочный мост
    
    Решение: динамическое программирование, жадные алгоритмы, O(n*log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<ll> vl;
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        vi a(n); for (auto &it : a) { std::cin >> it; }
        std::sort(all(a));
        vl answ(n);
        answ[0] = a[0];
        if (n >= 2) {
            answ[1] = a[1];
        }
        for (int i = 2; i < n; ++i) {
            answ[i] = std::min(
                answ[i-1] + a[0] + a[i],
                answ[i-2] + a[1] + a[0] + a[i] + a[1]
            );
        }
        std::cout << answ.back() << std::endl;
    }
    return 0;
}