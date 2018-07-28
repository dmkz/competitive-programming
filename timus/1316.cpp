/*
    Problem: 1316. Electronic Auction
    
    Solution: Segment Tree, O(q log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>

struct SegmentTree {
    
    int size;
    
    std::vector<int> data;
    
    SegmentTree() : size(0) { }
    
    SegmentTree(const std::vector<int>& arr) {
        build(arr);
    }
    
    inline void build(const std::vector<int>& arr) {
        size = (int)arr.size();
        int pow = 1;
        while (pow < size) pow *= 2;
        data.resize(2 * pow);
        if (size > 0) {
            build(0, 0, size-1, arr);
        }
    }
    
    inline void build(int v, int l, int r, const std::vector<int>& arr) {
        if (l == r) {
            data[v] = arr[l];
        } else {
            int m = (l + r) / 2;
            build(2*v+1,   l, m, arr);
            build(2*v+2, m+1, r, arr);
            data[v] = data[2*v+1]+data[2*v+2];
        }
    }
    
    inline int get(int v, int l, int r, int ql, int qr) const {
        if (l == ql && r == qr) {
            return data[v];
        } else {
            int m = (l + r) / 2;
            if (qr <= m) {
                return get(2*v+1,   l, m, ql, qr);
            } else if (ql > m) {
                return get(2*v+2, m+1, r, ql, qr);
            } else {
                return get(2*v+1, l, m, ql, m)+get(2*v+2, m+1, r, m+1, qr);
            }
        }
    }
    
    inline int get(int left, int right) const {
        assert(left <= right);
        return get(0, 0, size-1, left, right);
    }
    
    inline void inc(int v, int l, int r, int pos, int value) {
        if (l == r) {
            data[v] += value;
        } else {
            int m = (l + r) / 2;
            if (pos <= m) {
                inc(2*v+1,   l, m, pos, value);
            } else {
                inc(2*v+2, m+1, r, pos, value);
            }
            data[v] = data[2*v+1]+data[2*v+2];
        }
    }
    
    inline void inc(int pos, int value) {
        assert(pos < size);
        inc(0, 0, size-1, pos, value);
    }
};

int main() {
    const int SMAX = 1000000;
    SegmentTree st(std::vector<int>(1+SMAX,0));
    int64_t answ = 0;
    while (true) {
        char buf[5];
        scanf("%s", buf);
        double sum; scanf("%lf", &sum);
        int pos = (int)std::round(sum*100);
        if (buf[0] == 'Q') {
            break;
        } else if (buf[0] == 'B') {
            st.inc(pos, 1);
        } else if (buf[0] == 'D') {
            st.inc(pos,-1);
        } else if (buf[0] == 'S') {
            int limit; scanf("%d", &limit);
            answ += std::min(limit, st.get(pos, SMAX));
        }
    }
    printf("%0.2f", double(answ/100.0));
    return 0;
}