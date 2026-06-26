// xor, sparse table, O(n * log(n) + q * log(n)^2)
// Задача: G, Вердикт: OK, Время: 203ms, Память: 34.16Mb
#include <bits/stdc++.h>
#include <cassert>

const int PMAX = 19, NMAX = (1 << 18);

using pii = std::pair<int,int>;
using vpii = std::vector<pii>;

pii st[PMAX][NMAX];

pii merge(pii a, pii b) {
    return pii(std::min(a.first, b.first),
               std::max(a.second, b.second));
}

pii query(int l, int r) {
    int len = r - l + 1;
    int p = std::__lg(len);
    return merge(st[p][l], st[p][r-(1<<p)+1]);
}

pii query(int l, int r, int x) {
    l ^= x; r ^= x;
    if (r < l) std::swap(l, r);
    return query(l, r);
}

auto decompose(int l, int r, int x) {
    vpii res;
    while (l <= r) {
        int pw = 0;
        while (
            l + (1 << (pw+1)) - 1 <= r &&
            (l & ((1 << (pw+1)) - 1)) == 0
        )
            pw++;
        int sz = (1 << pw);
        int xl = (l ^ x) & ~(sz-1);
        res.push_back({xl, xl + sz - 1});
        l += sz;
    }
    return res;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, q; std::cin >> n >> q;
    for (int i = 0, ai; i < n; i++) {
        std::cin >> ai;
        st[0][ai] = {i, i};
    }
    for (int i = n; i < NMAX; i++)
        st[0][i] = {INT_MAX, INT_MIN};
    for (int p = 1; p < PMAX; p++)
        for (int i = 0; i + (1 << p) - 1 < n; i++)
            st[p][i] = merge(st[p-1][i], st[p-1][i+(1<<(p-1))]);
    int totalXor = 0;
    while (q --> 0) {
        int t; std::cin >> t;
        if (t == 1) {
            int x; std::cin >> x;
            totalXor ^= x;
        } else {
            assert(t == 2);
            int l, r; std::cin >> l >> r;
            pii answ{INT_MAX, INT_MIN};
            for (const auto &[li, ri] : decompose(l,r,totalXor))
                answ = merge(answ, query(li, ri));
            std::cout << answ.second - answ.first + 1 << '\n';
        }
    }
}
