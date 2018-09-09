/*
    Problem: 762C. Two strings
    
    Solution: binary search, dynamic programming, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::string a, b;
    std::cin >> a >> b;
    a = "$" + a + "#";
    b = "$" + b + "#";
    
    std::vector<int> suff(b.size(), -1);
    std::vector<int> pref(b.size(), (int)a.size());    
    
    {
        int pa = (int)a.size()-1;
        int pb = (int)b.size()-1;
        while (pa >= 0 && pb >= 0) {
            while (pa >= 0 && a[pa] != b[pb]) --pa;
            suff[pb] = pa;
            --pa; --pb;
        }
    }
    
    {
        int pa = 0, pb = 0;
        while (pa < (int)a.size() && pb < (int)b.size()) {
            while (pa < (int)a.size() && a[pa] != b[pb]) ++pa;
            pref[pb] = pa;
            ++pa, ++pb;
        }
    }
    int best_begin = 1, best_after = (int)b.size()-1;
    
    for (int pb = 0; pb+1 < (int)b.size(); ++pb) {
        if (pref[pb] == (int)a.size()) break;
        if (pref[pb] < suff[pb+1]) {
            best_begin = 0;
            best_after = 0;
        }
        int low = pb, high = (int)b.size()-1; // till which symbol erase
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (suff[mid] <= pref[pb]) {
                low = mid;
            } else {
                high = mid;
            }
        }
        // Answer is - high
        if (high - pb - 1 < best_after-best_begin) {
            best_begin = pb+1;
            best_after = high;
        }
    }
    b.erase(best_begin, best_after-best_begin);
    if (b.front() == '$') b = b.substr(1);
    if (b.back() == '#') b.pop_back();
    if (b.empty()) b = "-";
    std::cout << b;
    return 0;
}