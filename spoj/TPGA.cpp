/*
    Problem: TPGA - The Permutation Game Again
    
    Solution: Segment Tree, permutations, math, O(t*n*log(n))
*/

#pragma GCC optimize ("O3")

#include <iostream>
#include <vector>

struct SegmentTree {
    
    const int size;
    
    std::vector<int> data;
    
    // Build Segment Tree from array in O(n) time:
    inline void build(int v, int l, int r, const std::vector<int>& arr) {
        if (l == r) {
            data[v] = arr[l];
        } else {
            int m = (l + r) / 2;
            build(2*v+1,   l, m, arr);
            build(2*v+2, m+1, r, arr);
            data[v] = data[2*v+1] + data[2*v+2];
        }
    }
    
    // Set-query: set item `value` on position `pos` in O(log(n))
    // arr[pos] = value
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
            data[v] = data[2*v+1] + data[2*v+2];
        }
    }
    
    inline void set(int pos, int value) {
        set(0, 0, size-1, pos, value);
    }
    
    // Get-query: get sum of items on segment [ql, qr] in O(log(n))
    // arr[ql] + arr[ql+1] + ... + arr[qr-1] + arr[qr]
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
                return get(2*v+1,   l, m, ql, m) + get(2*v+2, m+1, r, m+1, qr);
            }
        }
    }
    
    inline int get(int left, int right) const {
        return get(0, 0, size-1, left, right);
    }
    
    // Construct Segment Tree from array:
    SegmentTree(const std::vector<int>& arr) : size((int)arr.size()) {
        int pow = 1;
        while (pow < size) pow *= 2;
        data.resize(2 * pow);
        build(0, 0, size-1, arr);
    }
};

const int mod = (int)1e9+7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::vector<int> fact{1};
    
    int nTest; std::cin >> nTest;
    while (nTest--) {
        
        // Input number of items in permutation:
        int n; std::cin >> n;
        
        // Precalculate factorials:
        for (int i = (int)fact.size(); i <= n; ++i) {
            fact.push_back(int(1LL * fact.back() * i % mod));
        }
        
        // Build SegmentTree:
        SegmentTree st(std::vector<int>(1+n, 1));
        st.set(0,0); // erase zero element
        
        // Get index of permutation:
        int index = 1;
        for (int i = n-1; i >= 0; --i) {
            int value; std::cin >> value;
            // Skip all permutations before item `value`:
            index += int(1LL * st.get(0, value-1) * fact[i] % mod); 
            if (index >= mod) index -= mod;
            // Erase item `value` and step to the next item:
            st.set(value, 0);
        }
        std::cout << index << '\n';
    }
    
    return 0;
}