#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
using namespace std;

template<typename T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

using pii = pair<int,int>;
using sii = set<pii>;
using vpii = vector<pii>;

int main() {
    ios::sync_with_stdio(false);
    
    int n, q; cin >> n >> q;
    vector<sii> segs(q+1); // {R, L}
    // 1 2 2 2 4 4 5 -> (1, -0) (2, -0) (2, -1) (2, -2) (4, -0) (4, -1), (5, -0)
    ordered_set<pii> plus, minus;
    auto insertInSet = [&](auto &dst, int x) {
        auto it = dst.lower_bound(pii(x, INT_MIN));
        if (it != dst.end() && it->first == x) {
            dst.insert(pii(x, it->second-1));
        } else {
            dst.insert(pii(x, 0));
        }
    };
    auto insertSingleSegment = [&](int l, int r) {
        insertInSet(plus, l);
        insertInSet(minus, r+1);
    };
    auto eraseSingleSegment = [&](int l, int r) {
        insertInSet(minus, l);
        insertInSet(plus, r+1);
    };
    auto count = [&](int k) {
        return plus.order_of_key(pii(k, INT_MAX)) - 
               minus.order_of_key(pii(k, INT_MAX));
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