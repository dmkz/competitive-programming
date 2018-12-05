/*
    Problem: 687C. The Values You Can Make
    
    Solution: dynamic programming, O(n^3)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

#define all(x) (x).begin(), (x).end()
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

vi solve(const int needSum, const vi& coins) {
    vvi curr(1+needSum, vi(1+needSum,0)); 
    curr[0][0] = true;
    auto next = curr;    
    for (auto coin : coins) {
        for (int sum = 0; sum + coin <= needSum; ++sum) {
            for (int cnt = 0; cnt <= needSum; ++cnt) {
                if (curr[sum][cnt]) {
                    next[sum+coin][cnt] = true;
                    next[sum+coin][sum+coin-cnt] = true;
                }
            }
        }
        curr = next;
    }
    return curr[needSum];
}

int main() {
    int nCoins, needSum;
    while (std::cin >> nCoins >> needSum) {
        std::vector<int> coins(nCoins);
        for (auto &it : coins) {
            std::cin >> it;
        }
        std::sort(coins.begin(), coins.end());
        auto isPossible = solve(needSum, coins);
        vi answ;
        for (int i = 0; i <= needSum; ++i) {
            if (isPossible[i]) {
                answ.push_back(i);
            }
        }
        std::cout << answ.size() << std::endl;
        for (auto it : answ) {
            std::cout << it << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}