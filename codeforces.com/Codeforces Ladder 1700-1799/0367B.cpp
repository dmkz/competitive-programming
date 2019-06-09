/*
    Problem: 367B. Sereja ans Anagrams
    
    Solution: sorting, binary search, two pointers, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
typedef std::vector<int> vi;
template<typename X, typename Y> int lowpos(const X& x, const Y& y) {
    return int(std::lower_bound(all(x), y) - x.begin());
}
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n, m, p; std::cin >> n >> m >> p; ) {
        vi a(n), b(m), x;
        for (auto &it : a) { std::cin >> it; x.push_back(it); }
        for (auto &it : b) { std::cin >> it; x.push_back(it); }
        std::sort(all(x));
        x.erase(std::unique(all(x)),(x).end());
        for (auto &it : a) { it = lowpos(x,it); }
        for (auto &it : b) { it = lowpos(x,it); }
        vi tmp, cnt(isz(x)), answ;
        int nZeros = isz(cnt);
        auto inc = [&](int item, int delta) {
            nZeros -= (cnt[item] == 0);
            cnt[item] += delta;
            nZeros += (cnt[item] == 0); 
        };
        for (auto it : b) {
            inc(it, +1); 
        }
        for (int q = 0; q < p; q++) {
            tmp.clear();
            for (int i = q; i < isz(a); i += p) {
                tmp.push_back(a[i]);
            }
            if (m > isz(tmp)) continue;
            for (int i = 0; i < m; i++) {
                inc(tmp[i], -1);
            }
            if (nZeros == isz(cnt)) { answ.push_back(q); }
            for (int i = 1; i + m - 1 < isz(tmp); i++) {
                inc(tmp[i-1],+1);
                inc(tmp[i+m-1],-1);
                if (nZeros == isz(cnt)) { answ.push_back(q + p * i); }
            }
            for (int i = 1; i <= m; i++) {
                inc(tmp[isz(tmp)-i],+1);
            }
        }
        std::sort(all(answ));
        std::cout << isz(answ) << "\n";
        for (auto it : answ) { std::cout << it+1 << ' '; }
        std::cout << std::endl;
    }
    return 0;
}