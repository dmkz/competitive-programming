/*
    Problem: 332B. Maximum Absurdity
    Solution: dynamic programming
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cerr.tie(0); std::cout.tie(0);
    
    int n, k; std::cin >> n >> k;
    std::vector<int> x(n); 
    for (auto& it : x) std::cin >> it;
    std::vector<ll> sum(n-k+1);
    for (int i = 0; i < k; ++i) {
        sum[0] += x[i];
    }
    for (int i = 1; i + k - 1 < n; ++i) {
        sum.at(i) = sum.at(i-1) - x.at(i-1) + x.at(i + k - 1);
    }
    std::vector<int> imax(sum.size());
    imax.back() = (int)sum.size()-1;
    for (int i = (int)sum.size()-2; i >= 0; --i) {
        if (sum[i] >= sum[imax[i+1]]) {
            imax[i] = i;
        } else {
            imax[i] = imax[i+1];
        }
    }
    int a = -1, b = -1; ll best = 0;
    for (int i = 0; i + 2 * k - 1 < n; ++i) {
        ll temp = sum[i] + sum[imax[i+k]];
        if (temp > best) {
            best = temp;
            a = i;
            b = imax[i+k];
        }
    }
    assert(a != -1 && b != -1);
    std::cout << a+1 << ' ' << b+1;
    return 0;
}