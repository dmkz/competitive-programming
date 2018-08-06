/*
    Problem: 702E. Analysis of Pathes in Functional Graph
    
    Solution: sparse table, graph, O(n log(k))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

const int NMAX = 100000;
const int PMAX = 34; // 10^10 <= 1024*1024*1024*16 = 2^34

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; ll k; std::cin >> n >> k;
    
    int next[1+PMAX][1+NMAX]; 
    int  min[1+PMAX][1+NMAX];
    ll   sum[1+PMAX][1+NMAX];
    
    for (int i = 0; i < n; ++i) {
        int next_; std::cin >> next_;
        next[0][i] = next_;
    }
    
    for (int i = 0; i < n; ++i) {
        int weight; std::cin >> weight;
        sum[0][i] = min[0][i] = weight;
    }

    for (int p = 1; p <= PMAX; ++p) {
        for (int i = 0; i < n; ++i) {
            int next_ = next[p-1][i];
            next[p][i] = next[p-1][next_];
            min[p][i] = std::min(min[p-1][i], min[p-1][next_]);
            sum[p][i] = sum[p-1][i] + sum[p-1][next_];
        }
    }

    for (int i = 0; i < n; ++i) {
        ll sum_ = 0; int min_ = (int)1e9, curr = i;
        for (int p = 0; p <= PMAX; ++p) {
            if (((k >> p) & 1) == 1) {
                min_ = std::min(min_, min[p][curr]);
                sum_ += sum[p][curr];
                curr = next[p][curr];
            }
        }
        std::cout << sum_ << ' ' << min_ << '\n';
    }
    
    return 0;
}