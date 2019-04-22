/*
    Problem: 363D. Renting Bikes
    
    Solution: binary search, greedy, sortings, O(n * log(n) + m * log(m))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
typedef std::vector<int> vi;
bool can(const vi& money, const vi& price, const int cnt, int rem, int& total) {
    int i = isz(money)-cnt, j = 0;
    total = 0;
    while (j < cnt) {
        int need = price[j] - money[i];
        if (need <= 0) {
            total += price[j];
        } else if (need > rem) {
            total = 0;
            return false;
        } else {
            rem -= need;
            total += money[i];
        }
        i++,j++;
    }
    total = std::max(0, total - rem);
    return true;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n, m, a; std::cin >> n >> m >> a; ) {
        std::vector<int> money(n), price(m);
        for (auto &it : money) { std::cin >> it; }
        for (auto &it : price) { std::cin >> it; }
        std::sort(all(money));
        std::sort(all(price));
        int low = 0, high = std::min(n,m)+1;
        while (high - low > 1) {
            int mid = (low + high) / 2, tmp;
            if (can(money,price,mid,a,tmp)) { low = mid; }
            else { high = mid; }
        }
        int answ;
        assert(can(money,price,low,a,answ));
        std::cout << low << ' ' << answ << '\n';
    }
    return 0;
}