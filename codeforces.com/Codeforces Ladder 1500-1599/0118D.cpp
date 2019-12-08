/*
    Problem: 118D. Caesar's Legions
    Solution: dynamic programming, dfs
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    int n1, n2, k1, k2;
    std::cin >> n1 >> n2 >> k1 >> k2;
    
    int cache[2][101][101];
    std::fill(&cache[0][0][0], &cache[0][0][0]+2*101*101, -1);
    
    const int mod = (int)1e8;
    
    std::function<int(int,int,int)> solve = [&](const int type, const int n1_, const int n2_) {
        if (n1_ == 0) return int(n2_ <= k2);
        if (n2_ == 0) return int(n1_ <= k1);
        if (cache[type][n1_][n2_] == -1) {
            int answ = 0;
            if (type == 0) {
                for (int s1 = 1; s1 <= std::min(k1,n1_); ++s1) {
                    answ = (answ + solve(1-type, n1_-s1, n2_)) % mod;
                }
            } else {
                for (int s2 = 1; s2 <= std::min(k2,n2_); ++s2) {
                    answ = (answ + solve(1-type, n1_, n2_-s2)) % mod;
                }
            }
            cache[type][n1_][n2_] = answ;
        }
        return cache[type][n1_][n2_];
    };
    std::cout << (solve(0, n1, n2) + solve(1, n1, n2)) % mod;
    
    return 0;
}