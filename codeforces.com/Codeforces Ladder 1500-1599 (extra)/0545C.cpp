/*
    Problem: 545C. Woodcutters
    
    Solution: Segment Tree, sorting, dynamic programming, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#define all(x) (x).begin(), (x).end()

const int INF = (int)1e6;

typedef long long ll;

struct Pair {
    ll x, l, r;
};

struct SegmentTree {

    const int size;

    std::vector<int> data;

    SegmentTree(int size_, int value = -INF) : size(size_) {
        int pow = 1;
        while (pow < size) pow *= 2;
        data.resize(2*pow);
        build(0, 0, size-1, value);
    }
    
    void build(int v, int l, int r, int x) {
        if (l == r) {
            data[v] = x;
        } else {
            int m = (l+r) / 2;
            build(2*v+1, l,m,x);
            build(2*v+2,m+1,r,x);
            data[v] = std::max(data[2*v+1], data[2*v+2]);
        }
    }
    
    int get(int v, int l, int r, int ql, int qr) {
        if (l == ql && r == qr) {
            return data[v];
        } else {
            int m = (l+r) / 2;
            if (qr <= m) {
                return get(2*v+1,l,m,ql,qr);
            } else if (ql > m) {
                return get(2*v+2, m+1, r, ql, qr);
            } else {
                return std::max(get(2*v+1,l,m,ql,m),get(2*v+2, m+1, r, m+1, qr));
            }
        }
    }
    
    int get(int l, int r) {
        return get(0, 0, size-1, l, r);
    }
    
    void set(int v, int l, int r, int p, int x) {
        if (l == r) {
            data[v] = x;
        } else {
            int m = (l+r) / 2;
            if (p <= m) {
                set(2*v+1, l, m, p, x);
            } else {
                set(2*v+2, m+1, r, p, x);
            }
            data[v] = std::max(data[2*v+1], data[2*v+2]);
        }
    }
    
    void set(int p, int x) {
        set(0, 0, size-1, p, x);
    }
    
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n; std::cin >> n;
    std::vector<Pair> arr(n);
    std::vector<ll> coord, center;
    for (auto& it : arr) {
        ll x, h;
        std::cin >> x >> h;
        it = Pair{x, x-h, x+h};
        coord.insert(coord.end(), {x, x-1, x+1, x-h-1, x-h+1, x+h-1, x+h+1, x+h, x-h});
        center.push_back(x);
    }
    std::sort(all(coord));
    coord.erase(std::unique(all(coord)), coord.end());
    const int SIZE = (int)coord.size();
    for (auto& it : arr) {
        it.x = int(std::lower_bound(all(coord), it.x)-coord.begin());
        it.l = int(std::lower_bound(all(coord), it.l)-coord.begin());
        it.r = int(std::lower_bound(all(coord), it.r)-coord.begin());
    }
    for (auto& it : center) {
        it = int(std::lower_bound(all(coord), it)-coord.begin());
    }
    
    std::function<bool(ll,ll)> empty_segment = [&](ll l, ll r) {
        auto begin = std::lower_bound(all(center), l);
        auto after = std::upper_bound(all(center), r);
        return after-begin == 0;
    };
    
    SegmentTree st(SIZE, -INF);
    st.set(0,0);
    for (auto& it : arr) {
        if (empty_segment(it.l, it.x-1)) {
            auto max = st.get(0, it.l-1);
            if (st.get(it.x, it.x) < max+1) {
                st.set(it.x, max+1);
            }
        }
        if (empty_segment(it.x+1, it.r)) {
            auto max = st.get(0, it.x-1);
            if (st.get(it.r, it.r) < max+1) {
                st.set(it.r, max+1);
            }
        }
    }
    std::cout << st.get(0, SIZE-1);
    return 0;
}