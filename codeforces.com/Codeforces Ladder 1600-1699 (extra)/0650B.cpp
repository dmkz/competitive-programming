/*
    Problem: 650B. Image Preview
    
    Solution: two pointers, greedy, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int solve(int n, int tMove, int tRotate, int tTotal, std::string s) {
    // check if we cant see all photos:
    int cur = (n - 1) * tMove + n;
    for (int i = 0; i < n; ++i) {
        cur += (s[i] == 'w') * tRotate;
    }
    if (cur <= tTotal) {
        return n;
    }
    s += s;
    int lt = n, rt = n;
    cur = 1 + (s[n] == 'w') * tRotate;
    if (cur > tTotal) { // check if we cant see even first photo:
        return 0;
    }
    // move to the leftmost position:
    while (cur + 1 + tMove + (s[lt-1] == 'w') * tRotate <= tTotal) {
        cur += 1 + tMove + (s[lt-1] == 'w') * tRotate;
        --lt;
    }
    int answ = 0;
    while (lt <= n) {
        // move to the rightmost position for each left position:
        while (true) {
            int next = cur + 1 + tMove + (s[rt+1] == 'w') * tRotate;
            next += std::min(n-lt, rt+1-n) * tMove;
            if (next <= tTotal) {
                cur = next - std::min(n-lt, rt+1-n) * tMove;
                ++rt;
            } else {
                break;
            }
        }
        answ = std::max(answ, rt - lt + 1);
        cur = cur - 1 - tMove - (s[lt] == 'w') * tRotate;
        ++lt;
    }
    return answ;
}

int main() {
    int n, tMove, tRotate, tTotal;
    while (std::cin >> n >> tMove >> tRotate >> tTotal) {
        std::string s; std::cin >> s;
        std::cout << solve(n, tMove, tRotate, tTotal, s) << std::endl;
    }
    return 0;
}