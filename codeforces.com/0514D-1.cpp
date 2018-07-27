/*
    Problem: 514D. R2D2 and Droid Army
    
    Solution: two pointers, Segment Tree, O(m*n*log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#pragma GCC optimize("O3")
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

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
        build(0, 0, size-1, arr);
    }
    
    inline void build(int v, int l, int r, const std::vector<int>& arr) {
        if (l == r) {
            data[v] = arr[l];
        } else {
            int m = (l + r) / 2;
            build(2*v+1,   l, m, arr);
            build(2*v+2, m+1, r, arr);
            data[v] = std::max(data[2*v+1], data[2*v+2]);
        }
    }
    
    inline void set(int v, int l, int r, int pos, int value) {
        if (l == r) {
            data[v] = value;
        } else {
            int m = (l + r) / 2;
            if (pos <= m) {
                set(2*v+1,   l, m, pos, value);
            } else {
                set(2*v+2, m+1, r, pos, value);
            }
            data[v] = std::max(data[2*v+1], data[2*v+2]);
        }
    }
    
    inline void set(int pos, int value) {
        assert(0 <= pos && pos < size);
        set(0, 0, size-1, pos, value);
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
                return std::max(get(2*v+1,   l, m, ql, m), get(2*v+2, m+1, r, m+1, qr));
            }
        }
    }
    
    inline int get(int left, int right) const {
        assert(left <= right);
        return get(0, 0, size-1, left, right);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nRobots, nTypes, nShots;
    std::cin >> nRobots >> nTypes >> nShots;
    
    std::vector<std::vector<int>> arr(nTypes, std::vector<int>(nRobots));
    
    for (int r = 0; r < nRobots; ++r) {
        for (int t = 0; t < nTypes; ++t) {
            std::cin >> arr[t][r];
        }
    }
    
    std::vector<SegmentTree> st(nTypes);
    
    for (int t = 0; t < nTypes; ++t) {
        st[t].build(arr[t]);
    }
    
    int l = 0, r = 0, blen = 0; // [l, r)
    std::vector<int> max(nTypes, 0);
    std::vector<int> best(nTypes, 0);
    
    while (l < nRobots) {
        assert(r >= l);
        
        while (r < nRobots) {
            int need = 0;
            for (int t = 0; t < nTypes; ++t) {
                need += std::max(max[t], arr[t][r]);
            }
            
            if (need > nShots) {
                break;
            }
            
            for (int t = 0; t < nTypes; ++t) {
                max[t] = std::max(max[t], arr[t][r]);
            }
            ++r;
        }
        
        if (r - l > blen) {
            best = max;
            blen = r-l;
        }
        
        ++l;
        r = std::max(l, r);
        
        if (r - l == 0) {
            max.assign(nTypes, 0);
        } else {
            for (int t = 0; t < nTypes; ++t) {
                max[t] = st[t].get(l, r-1);
            }
        }
    }
    
    for (auto& it : best) {
        std::cout << it << ' ';
    }
    return 0;
}