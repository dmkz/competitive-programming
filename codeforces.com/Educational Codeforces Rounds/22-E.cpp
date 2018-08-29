/*
    Problem: 813E. Army Creation
    
    Solution: Segment Tree, dynamic programming, O(n log(n)^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

struct SegmentTree {
    
    int size;
    
    std::vector<std::vector<int>> data;
    
    SegmentTree(const std::vector<int>& arr) {
        size = (int)arr.size();
        int pow = 1;
        while (pow < size) pow*=2;
        data.resize(2 * pow);
        build(0, 0, size-1, arr);
    }
    
    inline void build(int v, int l, int r, const std::vector<int>& arr) {
        if (l == r) {
            data[v] = {arr[l]};
        } else {
            int m = (l+r)/2;
            build(2*v+1, l, m, arr);
            build(2*v+2,m+1,r, arr);
            auto& lv = data[2*v+1];
            auto& rv = data[2*v+2];
            std::merge(lv.begin(), lv.end(), rv.begin(), rv.end(), std::back_inserter(data[v]));
        }
    }
    
    inline int query(int v, int l, int r, int ql, int qr, int x) const {
        // how many items > x
        if (l == ql && r == qr) {
            auto& dv = data[v];
            return int(dv.end() - std::upper_bound(dv.begin(), dv.end(), x));
        } else {
            int m = (l+r)/2;
            if (qr <= m) {
                return query(2*v+1, l, m, ql, qr, x);
            } else if (ql > m) {
                return query(2*v+2, m+1, r, ql,qr, x);
            } else {
                return query(2*v+1,l,m,ql,m,x) + query(2*v+2,m+1,r,m+1,qr,x);
            }
        }
    }
    
    inline int query(int l, int r, int x) const {
        return query(0, 0, size-1, l, r, x);
    }
};

const int AMAX = (int)1e5;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, k; std::cin >> n >> k;
    std::vector<int> a(n);
    for (auto& it : a) std::cin >> it;
    std::vector<std::vector<int>> pos(1+AMAX);
    std::vector<int> d(n, n);
    for (int i = n-1; i >= 0; --i) {
        auto& pi = pos[a[i]];
        if ((int)pi.size() >= k) {
            d[i] = pi[(int)pi.size()-k];
        }
        pi.push_back(i);
    }
    SegmentTree st(d);
    int last = 0, q; std::cin >> q;
    while (q--) {
        int x, y; std::cin >> x >> y;
        int l = (x + last) % n, r = (y + last) % n;
        if (l > r) std::swap(l,r);
        last = st.query(l,r,r);
        std::cout << last << '\n';
    }
    return 0;
}