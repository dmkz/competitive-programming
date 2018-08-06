/*
    Problem: 1016C. Vasya And The Mushrooms
    
    Solution: dynamic programming, prefix sums, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

typedef long long ll;

struct PrefSum {
    
    std::vector<ll> sum1; // arr[i] + arr[i+1] + ... + arr[n-1]
    std::vector<ll> sum2; // arr[i] + 2 * arr[i+1] + 3 * arr[i+2] + ... +
    std::vector<ll> sum3; // (n-i) * arr[i] + ... + arr[n]
    
    PrefSum(const std::vector<ll>& arr) {
        int n = (int)arr.size();
        sum1.resize(n+1);
        for (int i = n-1; i >= 0; --i) {
            sum1[i] = sum1[i+1] + arr[i];
        }
        
        sum2.resize(n+1);
        sum3.resize(n+1);
        // sum[0] = arr[0] + arr[1] * 2 + arr[2] * 3 + arr[3] * 4
        // sum[n-1] = arr[n-1]
        for (int i = n-1; i >= 0; --i) {
            sum2[i] = sum2[i+1] + sum1[i];
        }
        for (int i = n-1; i >= 0; --i) {
            sum3[i] = (n-i) * arr[i] + sum3[i+1];
        }
    }

    inline ll from_left_to_right(ll start_time, int pos) const {
        return sum2[pos] + sum1[pos] * (start_time-1);
    }
    
    inline ll from_right_to_left(ll start_time, int pos) const {
        return sum3[pos] + sum1[pos] * (start_time-1);
    }
    
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    
    std::vector<ll> a(n), b(n);
    for (auto& it : a) std::cin >> it;
    for (auto& it : b) std::cin >> it;
        
    PrefSum sa(a), sb(b);
    ll res = 0, answ = 0;
    for (int i = 0; i < n; ++i) {
        ll temp = 0;
        if (i % 2 == 0) {
            temp = res + sa.from_left_to_right(2 * i, i) + sb.from_right_to_left(2*i+n-i, i);
            res += 2 * i * a[i] + (2 * i + 1) * b[i];
        } else {
            temp = res + sb.from_left_to_right(2 * i, i) + sa.from_right_to_left(2*i+n-i, i);
            res += 2 * i * b[i] + (2 * i + 1) * a[i];
        }
        answ = std::max(answ, temp);
    }
    answ = std::max(answ, res);
    std::cout << answ;
    return 0;
}