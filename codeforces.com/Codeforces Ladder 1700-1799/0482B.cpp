/*
    Problem: 482B. Interesting Array
    
    Solution: greedy, bitmasks, sparse table, O(n * log(MAX))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define getbit(mask,i) ((mask >> i) & 1)
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
struct Seg { int l, r, x; };
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int nItems, nSeg;
    while (std::cin >> nItems >> nSeg) {
        std::vector<Seg> segs(nSeg);
        vvi events(1+nItems);
        for (auto & s : segs) {
            std::cin >> s.l >> s.r >> s.x;
            s.l--;
            events[s.l].push_back(+s.x);
            events[s.r].push_back(-s.x);
            s.r--;
        }
        vi arr(nItems), cnt(30);
        for (int i = 0; i < isz(arr); ++i) {
            for (auto it : events[i]) {
                const int x = std::abs(it);
                for (int bit = 29; bit >= 0; --bit) {
                    if (getbit(x,bit)) {
                        cnt[bit] += (it >= 0 ? +1 : -1);
                    }
                }
            }
            for (int bit = 29; bit >= 0; --bit) {
                if (cnt[bit]) {
                    arr[i] |= (1 << bit);
                }
            }
        }
        vi log2(1+nItems);
        for (int i = 2; i <= nItems; ++i) {
            log2[i] = log2[i/2] + 1;
        }
        vvi bitwise_and(30, vi(nItems));
        for (int i = 0; i < nItems; ++i) {
            bitwise_and[0][i] = arr[i];
        }
        for (int p = 1; p < 30; ++p) {
            for (int i = 0; i + (1 << p) - 1 < nItems; ++i) {
                bitwise_and[p][i] = bitwise_and[p-1][i] & bitwise_and[p-1][i + (1 << (p-1))];
            }
        }
        bool ok = true;
        for (const auto & s : segs) {
            auto p = log2[s.r-s.l+1];
            int res = bitwise_and[p][s.l] & bitwise_and[p][s.r + 1 - (1 << p)];
            ok = ok && (res == s.x);
        }
        if (!ok) {
            std::cout << "NO" << std::endl;
        } else {
            std::cout << "YES\n";
            for (auto &it : arr) { std::cout << it << ' '; }
            std::cout << std::endl;
        }
    }
    return 0;
}