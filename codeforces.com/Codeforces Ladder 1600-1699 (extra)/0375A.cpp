/*
    Problem: 375A. Divisible by Seven
    
    Solution: number theory, strings, brute force, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    std::string s;
    while (std::cin >> s) {
        std::vector<int> cnt(10,0);
        for (auto it : s) {
            cnt[int(it-'0')]++;
        }
        std::string tail, mid, head;
        while (cnt[0] > 0) {
            tail += "0";
            cnt[0]--;
        }
        mid = "1689";
        cnt[1]--,cnt[6]--,cnt[8]--,cnt[9]--;
        for (int i = 0; i < 10; ++i) {
            while (cnt[i] > 0) {
                head += char(i+'0');
                cnt[i]--;
            }
        }
        int need = 0;
        for (auto it : head) {
            need = (need * 10 + (it - '0')) % 7;
        }
        int tailPow = 1;
        for (int i = 0; i < (int)tail.size(); ++i) {
            (tailPow *= 10) %= 7;
        }
        (need *= tailPow) %= 7;
        for (int i = 0; i < 4; ++i) {
            (need *= 10) %= 7;
        }
        bool flag = false;
        do {
            int rem = 0;
            for (char c : mid) {
                rem = (rem * 10 + (c - '0')) % 7;
            }
            (rem *= tailPow) %= 7;
            if ((need + rem) % 7 == 0) {
                flag = true;
                break;
            }
        } while (std::next_permutation(mid.begin(), mid.end()));
        assert(flag);
        std::cout << head << mid << tail << std::endl;
    }
    return 0;
}