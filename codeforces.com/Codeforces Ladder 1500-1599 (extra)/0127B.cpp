/*
    Problem: 127B. Canvas Frames
    
    Solution: greedy, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    
    std::vector<int> cnt(1+100);
    while (n--) {
        int a; std::cin >> a; cnt[a]++;
    }
    int answ = 0;
    for (int i = 1; i <= 100; ++i) {
        while (cnt[i] >= 4) {
            cnt[i] -= 4;
            answ++;
        }
    }
    for (int i = 1; i <= 100; ++i) {
        for (int j = i+1; j <= 100; ++j) {
            if (cnt[i] >= 2 && cnt[j] >= 2) {
                cnt[i] -= 2;
                cnt[j] -= 2;
                answ++;
            }
        }
    }
    
    std::cout << answ;
    return 0;
}