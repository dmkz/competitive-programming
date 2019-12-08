/*
    Problem: 165C. Another Problem on Strings
    Solution: binary search, two pointers, strings, dynamic programming
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
typedef long long ll;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int need; std::cin >> need;
    
    std::string s; std::cin >> s;
    
    std::vector<int> sum{0};
    for (auto c : s) {
        sum.push_back(sum.back() + int(c - '0'));
    }
    
    const int n = (int)s.size();
    std::vector<int> mxz(1+n);
    for (int i = n-1; i >= 0; --i) {
        mxz[i] = (s[i] == '0') ? (mxz[i+1] + 1) : 0;
    }
    ll answ = 0;
    for (int pos = 0; pos < n; ++pos) {
        if (sum[pos+1]-sum[pos] > need) {
            continue;
        }
        if (sum[pos+1]-sum[pos] == need) {
            answ += 1 + mxz[pos+1];
            continue;
        }
        int low = pos, high = n;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (sum[mid+1]-sum[pos] < need) {
                low = mid;
            } else {
                high = mid;
            }
        }
        // Сумма до low меньше чем нужно!
        int first = low+1;
        if (first >= n) continue;
        answ += 1 + mxz[first+1];
    }
    std::cout << answ;
    
    return 0;
}