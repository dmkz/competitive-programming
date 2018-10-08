/*
    Problem: 706C. Hard problem
    
    Solution: strings, dynamic programming, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
typedef long long ll;
const ll INF = (ll)1e18L;
int main() {
    int n; std::cin >> n;
    std::vector<int> cost(n);
    for (auto& it : cost) std::cin >> it;
    std::vector<std::string> original(n), reversed(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> original[i]; reversed[i] = original[i];
        std::reverse(reversed[i].begin(), reversed[i].end());
    }
    std::vector<ll> min_original(n, INF), min_reversed(n, INF);
    min_original[0] = 0; min_reversed[0] = cost[0];
    for (int i = 1; i < n; ++i) {
        if (original[i-1] <= original[i]) {
            min_original[i] = std::min(min_original[i], min_original[i-1]);
        }
        if (reversed[i-1] <= original[i]) {
            min_original[i] = std::min(min_original[i], min_reversed[i-1]);
        }
        if (original[i-1] <= reversed[i]) {
            min_reversed[i] = std::min(min_reversed[i], min_original[i-1] + cost[i]);
        }
        if (reversed[i-1] <= reversed[i]) {
            min_reversed[i] = std::min(min_reversed[i], min_reversed[i-1] + cost[i]);
        }
    }
    ll answ = std::min(min_original.back(), min_reversed.back());
    if (answ == INF) answ = -1;
    std::cout << answ;
    return 0;
}