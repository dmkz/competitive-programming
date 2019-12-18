/*
    Problem: 220B. Little Elephant and Array
    Solution: Mo's algorithm, two pointers, queries offline, O(n + q*(log(q) + sqrt(n)))
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
const int AMAX = (int)1e5;
using vi = std::vector<int>;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n, q; std::cin >> n >> q; ) {
        vi arr(n); for (auto &it : arr) { std::cin >> it; it = std::min(it, AMAX); }
        vi cnt(1+AMAX);
        struct Query { int l, r, id; };
        std::vector<Query> queries(q);
        for (int i = 0; i < q; i++) {
            auto &it = queries[i];
            std::cin >> it.l >> it.r;
            it.l--; it.r--;
            it.id = i;
        }
        const int gsize = 317;
        std::sort(all(queries), [](auto a, auto b){
            const int ga = a.l / gsize, gb = b.l / gsize;
            if (ga < gb) { return true; }
            else if (ga > gb) { return false; }
            return ga % 2 == 0 ? a.r < b.r : a.r > b.r;
        });
        vi answ(q);
        int curr = 0, l = 0, r = -1;
        auto inc = [&](int p) {
            const int item = arr[p];
            curr -= (cnt[item] == item);
            cnt[item]++;
            curr += (cnt[item] == item);
        };
        auto dec = [&](int p) {
            const int item = arr[p];
            curr -= (cnt[item] == item);
            cnt[item]--;
            curr += (cnt[item] == item);
        };
        for (auto &it : queries) {
            while (r < it.r) { inc(++r); }
            while (l > it.l) { inc(--l); }
            while (r > it.r) { dec(r--); }
            while (l < it.l) { dec(l++); }
            answ[it.id] = curr;
        }
        for (auto & it : answ) { std::cout << it << '\n'; }
    }
    return 0;
}