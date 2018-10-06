/*
    Problem: 91B. Queue
    
    Solution: SegmentTree, sorting, binary search, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

struct SegmentTree {
    
    int size;
    
    std::vector<int> data;
    
    SegmentTree(const std::vector<int>& arr) {
        size = (int)arr.size();
        int pow = 1;
        while (pow < size) pow *= 2;
        data.resize(2*pow);
        build(0,0,size-1,arr);
    }
    
    void build(int v, int l, int r, const std::vector<int>& arr) {
        if (l == r) {
            data[v] = arr[l];
        } else {
            int m = (l + r) / 2;
            build(2*v+1, l, m, arr);
            build(2*v+2,m+1,r, arr);
            data[v] = std::max(data[2*v+1], data[2*v+2]);
        }
    }
    
    int get(int v, int l, int r, int ql, int qr) {
        if (l == ql && r == qr) {
            return data[v];
        } else {
            int m = (l + r) / 2;
            if (qr <= m) {
                return get(2*v+1,l,m,ql,qr);
            } else if (ql > m) {
                return get(2*v+2,m+1,r,ql,qr);
            } else {
                return std::max(
                    get(2*v+1,l,m,ql,m), 
                    get(2*v+2,m+1,r,m+1,qr)
                );
            }
        }
    }

    int get(int l, int r) {
        return get(0,0,size-1,l,r);
    }
};

int main() {
    int n; std::cin >> n;
    std::vector<int> arr(n);
    std::vector<int> coord{0};
    for (auto& it : arr) {
        std::cin >> it;
        coord.push_back(it);
    }
    std::sort(coord.begin(), coord.end());
    std::vector<int> cnt(1+n);
    for (int i = 0; i < n; ++i) {
        int pos = int(std::lower_bound(coord.begin(), coord.end(), arr[i])-coord.begin());
        arr[i] = pos + cnt[pos];
        cnt[pos]++;
    }
    std::vector<int> pos(1+n,0);
    for (int i = 0; i < n; ++i) {
        pos[arr[i]] = i;
    }
    SegmentTree st(pos);
    for (int i = 0; i < n; ++i) {
        int ret = st.get(0, arr[i]);
        std::cout << std::max(-1,ret-i-1) << ' ';
    }
    return 0;
}