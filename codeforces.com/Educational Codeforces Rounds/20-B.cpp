/*
    Problem: 803B. Distances to Zero
    
    Solution: dynamic programming, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
const int INF = (int)1e9+1;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int main() {
    int n; std::cin >> n;
    vi a(n); for (auto& it : a) std::cin >> it;
    vi suff(n+1,INF), pref(n+1,INF);
    for (int i = n-1; i >= 0; --i) {
        if (a[i] == 0) {
            suff[i] = 0;
        } else {
            suff[i] = suff[i+1] + 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (a[i] == 0) {
            pref[i+1] = 0;
        } else {
            pref[i+1] = pref[i]+1;
        }
    }
    for (int i = 0; i < n; ++i) {
        std::cout << std::min(pref[i+1], suff[i]) << ' ';
    }
    return 0;
}