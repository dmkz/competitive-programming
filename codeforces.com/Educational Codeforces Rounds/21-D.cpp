/*
    Problem: 808D. Array Division
    
    Solution: map, implementation, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<int> arr(1+n+1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> arr[i];
    }
    std::vector<ll> pref(1+n+1), suff(1+n+1);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i-1] + arr[i];
    }
    for (int i = n; i >= 1; --i) {
        suff[i] = suff[i+1] + arr[i];
    }
    std::map<ll,int> lcnt, rcnt;
    for (int i = 1; i <= n; ++i) {
        rcnt[arr[i]]++;
    }
    for (int i = 1; i <= n; ++i) {
        lcnt[arr[i]]++;
        rcnt[arr[i]]--;
        ll diff = pref[i]-suff[i+1];
        if (diff == 0) {
            std::cout << "YES"; return 0;
        }
        if (diff > 0) {
            if (diff % 2 != 0) continue;
            if (lcnt[diff/2] > 0) {
                std::cout << "YES"; return 0;
            }
        } else {
            diff = -diff;
            if (diff % 2 != 0) continue;
            if (rcnt[diff/2] > 0) {
                std::cout << "YES"; return 0;
            }
        }
    }
    std::cout << "NO";
    return 0;
}