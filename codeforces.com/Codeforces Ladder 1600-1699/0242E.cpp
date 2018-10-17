/*
    Problem: 242E. XOR on Segment
    
    Solution: Segment Tree, xor, O(n*log(n)^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

typedef long long ll;

struct Node {
    int sum, inv;
};

Node combine(const Node& a, const Node& b) {
    return Node{a.sum + b.sum, 0};
}

struct SegmentTree {

    int size;

    std::vector<Node> data;    
    
    SegmentTree(const std::vector<int>& arr) {
        size = (int)arr.size();
        int pow = 1;
        while (pow < size) pow *= 2;
        data.resize(2*pow);
        build(0, 0, size-1, arr);
    }

    void build(int v, int l, int r, const std::vector<int>& arr) {
        if (l == r) {
            data[v] = Node{arr[l], 0};
        } else {
            int m = (l + r) / 2;
            build(2*v+1,  l,m,arr);
            build(2*v+2,m+1,r,arr);
            data[v] = combine(data[2*v+1], data[2*v+2]);
        }
    }
    
    void push(int v, int l, int r) {
        if (data[v].inv) {
            int m = (l+r)/2;
            reverse(2*v+1,   l, m,   l, m);
            reverse(2*v+2, m+1, r, m+1, r);
        }
    }
    
    void reverse(int v, int l, int r, int ql, int qr) {
        ql = std::max(l, ql);
        qr = std::min(r, qr);
        if (r < l || qr < ql) return;
        if (l == ql && r == qr) {
            data[v].sum = r - l + 1 - data[v].sum;
            data[v].inv ^= 1;
            return;
        }
        int m = (l + r) / 2;
        push(v, l, r);
        reverse(2*v+1,   l, m, ql, qr);
        reverse(2*v+2, m+1, r, ql, qr);
        data[v] = combine(data[2*v+1], data[2*v+2]);
    }
    
    void reverse(int l, int r) {
        reverse(0, 0, size-1, l, r);
    }
    
    int get(int v, int l, int r, int ql, int qr) {
        ql = std::max(l, ql);
        qr = std::min(r, qr);
        if (r < l || qr < ql) return 0;
        if (l == ql && r == qr) {
            return data[v].sum;
        } else {
            push(v,l,r);
            int m = (l + r) / 2;
            int ret = 0;
            ret += get(2*v+1,l,m,ql,qr);
            ret += get(2*v+2,m+1,r,ql,qr);
            data[v] = combine(data[2*v+1], data[2*v+2]);
            return ret;
        }
    }
    
    int get(int l, int r) {
        return get(0, 0, size-1, l, r);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for (auto& it : arr) { std::cin >> it; }
    std::vector<SegmentTree> st;
    for (int bit = 0; bit < 20; ++bit) {
        std::vector<int> tmp(n);
        for (int i = 0; i < n; ++i) {
            tmp[i] = (arr[i] >> bit) & 1;
        }
        st.push_back(SegmentTree(tmp));
    }
    int nQ; std::cin >> nQ;
    while (nQ--) {
        int t, l, r;
        std::cin >> t >> l >> r;
        --l,--r;
        if (t == 1) {
            ll res = 0;
            for (int bit = 0; bit < 20; ++bit) {
                res += ((ll)st[bit].get(l, r) << bit);
            }
            std::cout << res << "\n";
        } else {
            int x; std::cin >> x;
            for (int bit = 0; bit < 20; ++bit) {
                if ((x >> bit) & 1) {
                    st[bit].reverse(l, r);
                }
            }
        }
    }
    return 0;
}