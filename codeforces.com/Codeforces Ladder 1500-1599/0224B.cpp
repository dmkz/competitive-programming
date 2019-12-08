/*
    Problem: 224B. Array
    Solution: two pointers
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, need;
    std::cin >> n >> need;
    
    std::vector<int> a(n); for (auto& it : a) std::cin >> it;
    
    std::vector<int> count(1+*std::max_element(a.begin(), a.end()));
    
    int l = 0, r = -1, nUniq = 0, best_l = -2, best_r = -2, best_len = (int)1e9;
    while (l < n) {
        while (r+1 < n && nUniq < need) {
            ++r;
            count[a[r]]++;
            if (count[a[r]] == 1) ++nUniq;
        }
        assert(r >= l);
        if (nUniq == need && best_len > r - l + 1) {
            best_len = r - l + 1;
            best_l = l;
            best_r = r;
        }
        count[a[l]]--;
        if (count[a[l]] == 0) --nUniq;
        ++l;
    }
    std::cout << best_l+1 << ' ' << best_r+1;
    return 0;
}