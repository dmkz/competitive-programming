// бинарный поиск по ответу
// Задача: C, Вердикт: OK, Время: 74ms, Память: 2.13Mb
#include <bits/stdc++.h>
using ll = long long;
using vi = std::vector<int>;
ll binSearchMax(const vi &a, int r) {
    ll low = 0, high = (ll)1e18L+1;
    while (high - low > 1) {
        ll mid = (low + high) / 2;
        ll s = 0, rating = 0;
        for (auto it : a) {
            s += it;
            if (s < 0) s = 0;
            if (s >= mid) {
                rating++;
                s = 0;
            }
        }
        if (rating < r) high = mid;
        else low = mid;
    }
    return low;
}
main() {
    int n, r; std::cin >> n >> r;
    vi a(n); for (auto &it : a) std::cin >> it;
    ll max = binSearchMax(a, r);
    ll min = binSearchMax(a, r+1)+1;
    if (min > max) std::cout << "-1\n";
    else std::cout << min << ' ' << max << std::endl;
}
