/*
    Problem: 629D. Babaei and Birthday Cake
    
    Solution: dynamic programming, segment tree, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef long double Real;

const Real PI = std::acos(Real(-1));

struct SegmentTree {

    int size;

    std::vector<ll> data;

    SegmentTree(const std::vector<ll>& arr) : size((int)arr.size()) {
        int pow = 1;
        while (pow < size) pow *= 2;
        data.resize(2*pow);
        build(0,0,size-1,arr);
    }
    
    void build(int v, int l, int r, const std::vector<ll>& arr) {
        if (l == r) {
            data[v] = arr[l];
        } else {
            int m = (l+r)/2;
            build(2*v+1,l,m,arr);
            build(2*v+2,m+1,r,arr);
            data[v] = std::max(data[2*v+1],data[2*v+2]);
        }
    }
    
    void set(int v, int l, int r, int p, ll x) {
        if (l == r) {
            data[v] = x;
        } else {
            int m = (l+r)/2;
            if (p <= m) {
                set(2*v+1,l,m,p,x);
            } else {
                set(2*v+2,m+1,r,p,x);
            }
            data[v] = std::max(data[2*v+1],data[2*v+2]);
        }
    }
    
    ll get(int v, int l, int r, int ql, int qr) {
        if (l == ql && r == qr) {
            return data[v];
        } else {
            int m = (l+r) / 2;
            if (qr <= m) {
                return get(2*v+1,l,m,ql,qr);
            } else if (ql > m) {
                return get(2*v+2,m+1,r,ql,qr);
            } else {
                return std::max(get(2*v+1,l,m,ql,m), get(2*v+2,m+1,r,m+1,qr));
            }
        }
    }
    
    void set(int p, ll x) {
        set(0,0,size-1,p,x);
    }
    ll get(int left, int right) {
        return get(0,0,size-1,left,right);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<ll> arr(n), item(1,0);
    for (int i = 0; i < n; ++i) {
        int r, h; std::cin >> r >> h;
        arr[i] = 1LL * r * r * h;
        item.push_back(arr[i]);
    }
    std::sort(all(item));
    item.erase(std::unique(all(item)), item.end());
    int sz = (int)item.size();
    SegmentTree st(std::vector<ll>(sz,0));
    for (int i = 0; i < n; ++i) {
        int pos = int(std::lower_bound(all(item), arr[i])-item.begin());
        ll val = st.get(0, pos-1);
        st.set(pos, val+arr[i]);
    }
    std::cout << std::fixed << std::setprecision(6) << st.get(0, sz-1) * PI << std::endl;
    return 0;
}