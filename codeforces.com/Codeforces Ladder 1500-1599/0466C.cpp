/*
    Problem: 466C. Number of Ways
    Solution: brute force, dynamic programming, two pointers
*/
#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;

int main() {
    int n; std::cin >> n;
    std::vector<ll> sum{0};
    
    for (int i = 0; i < n; ++i) {
        int a; std::cin >> a;
        sum.push_back(sum.back() + a);
    }
    
    if (sum.back() % 3 != 0) {
        std::cout << 0;
        return 0;
    }
    
    // we need sum / 3 for one block
    ll need = sum.back() / 3;
    // find number of positions of `2 * need` after each position of `need` sum
    ll count2 = 0, answ = 0;
    for (int i = n-1; i >= 1; --i) {
        count2 += (sum[i] == 2 * need);
    }
    for (int i = 1; i < n; ++i) {
        if (sum[i] == 2 * need) {
            --count2;
        }
        if (sum[i] == need) {
            answ += count2;
        }
    }
    std::cout << answ;
    return 0;
}