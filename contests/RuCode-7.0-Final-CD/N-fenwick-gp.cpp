#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

using pii = pair<int,int>;
using sii = set<pii>;
using vpii = vector<pii>;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

struct Fenwick {
    int n;
    gp_hash_table<int, int, custom_hash> tree;
    Fenwick(int n_ = 0) : n(n_) { }
    void add(int p, int delta) {
        while (p < n) {
            tree[p] += delta;
            p |= p + 1;
        }
    }
    int get(int r) {
        int result = 0;
        while (r >= 0) {
            result += tree[r];
            r = (r & (r+1)) - 1;
        }
        return result;
    }
    
    int get(int l, int r) { return l > r ? 0 : get(r) - get(l-1); }
    
};

int main() {
    ios::sync_with_stdio(false);
    
    int n, q; cin >> n >> q;
    Fenwick fenw(n+1);
    vector<sii> segs(q+1); // {R, L}
    auto insertSingleSegment = [&](int l, int r) {
        fenw.add(l, +1);
        fenw.add(r+1, -1);
    };
    auto eraseSingleSegment = [&](int l, int r) {
        fenw.add(l, -1);
        fenw.add(r+1, +1);
    };
    auto count = [&](int k) {
        return fenw.get(k);
    };
    auto insert = [&](int x, int l, int r) {
        auto &s = segs[x];
        auto it = s.lower_bound(pii(l, 0));
        if (it != s.end() && it->second <= l) {
            l = it->second;
        }
        it = s.lower_bound(pii(r,0));
        if (it != s.end() && it->second <= r) {
            r = it->first;
        }
        while (true) {
            it = s.lower_bound(pii(l, 0));
            if (it != s.end() && it->first <= r) {
                eraseSingleSegment(it->second, it->first); // для дерева отрезков
                s.erase(it);
            } else break;
        }
        s.insert({r,l});
        insertSingleSegment(l, r); // для дерева отрезков
    };
    auto remove = [&](int x, int l, int r) {
        auto &s = segs[x];
        auto it = s.lower_bound(pii(l, 0));
        static vpii queue;
        queue.clear();
        if (it != s.end() && it->second <= l) {
            queue.emplace_back(it->second, l-1);
            l = it->second;
        }
        it = s.lower_bound(pii(r, 0));
        if (it != s.end() && it->second <= r) {
            queue.emplace_back(r+1, it->first);
            r = it->first;
        }
        while (true) {
            it = s.lower_bound(pii(l, 0));
            if (it != s.end() && it->first <= r) {
                eraseSingleSegment(it->second, it->first); // для дерева отрезков
                s.erase(it);
            } else break;
        }
        for (const auto &[nl, nr] : queue)
            if (nl <= nr) {
                s.insert(pii(nr, nl));
                insertSingleSegment(nl, nr); // для дерева отрезков
            }
    };
    for (int id = 1; id <= q; id++) {
        char c; cin >> c;
        if (c == '?') {
            // кол-во
            int k; cin >> k;
            cout << count(k) << endl;
        } else if (c == '+') {
            int l, r, x; cin >> l >> r >> x;
            assert(1 <= x && x <= q);
            // добавить
            insert(x, l, r);
        } else {
            assert(c == '-');
            int l, r, x; cin >> l >> r >> x;
            assert(1 <= x && x <= q);
            // удалить
            remove(x, l, r);
        }
    }
    return 0;
}