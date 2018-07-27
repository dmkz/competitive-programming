/*
    Problem: 514D. R2D2 and Droid Army
    
    Solution: two pointers, Sparse Table, O(m*n*log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#pragma GCC optimize("O3")
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

struct SparseTable {
    
    static std::vector<int> log2;
    
    std::vector<std::vector<int>> data;
    
    SparseTable() { }
    
    SparseTable(const std::vector<int>& arr) { build(arr); }
    
    void build(const std::vector<int>& arr) {
        assert(!log2.empty());
        data.clear();
        const int n = (int)arr.size();
        for (int i = (int)log2.size(); i <= n; ++i) {
            log2.push_back(log2[i / 2]+1);
        }
        data.reserve(log2[n]+1);
        data.push_back(arr);
        for (int pow = 1, len = 1; 2 * len <= n; ++pow, len *= 2) {
            data.push_back(std::vector<int>(n-2*len+1));
            for (int pos = 0; pos + 2 * len <= n; ++pos) {
                data[pow][pos] = std::max(
                    data[pow-1][pos], data[pow-1][pos+len]
                );
            }
        }
    }
       
    inline int get(int l, int r) const {
        const int level = log2.at(r-l+1);
        return std::max(data[level][l], data[level][r-(1 << level)+1]);
    }
};

std::vector<int> SparseTable::log2{0,0};

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
    
    std::vector<SparseTable> st(nTypes);
    
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