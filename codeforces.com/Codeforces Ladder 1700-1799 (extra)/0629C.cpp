/*
    Problem: 629C. Famil Door and Brackets
    
    Solution: dynamic programming, strings, brackets sequences, O(m+(n-m)^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<vvi> vvvi;

const int mod = (int)1e9+7;

int& add(int& a, int b) {
    return (a += b) >= mod ? (a -= mod) : a;
}

int solve(const int curr, const int need, const std::string& s) {
    int givenBalance = 0, minPref = 0;
    for (auto it : s) {
        givenBalance += (it == '(' ? +1 : -1);
        minPref = std::min(minPref, givenBalance);
    }
    if (std::abs(givenBalance) > need-curr) {
        return 0;
    }
    int mxLen = need - curr + 1;
    vvvi count(2, vvi(1+mxLen, vi(1+mxLen)));
    // count[used s][len][balance]
    count[0][0][0] = 1;
    for (int used = 0; used < 2; ++used) {
        for (int len = 0; len < mxLen; ++len) {
            for (int balance = 0; balance <= mxLen; ++balance) {
                const int currCnt = count[used][len][balance];
                if (balance > 0) {
                    add(count[used][len+1][balance-1], currCnt);
                }
                if (balance+1 <= mxLen) {
                    add(count[used][len+1][balance+1], currCnt);
                }
                if ( used == 0 &&
                    balance + minPref >= 0 && balance + minPref <= mxLen &&
                    balance + givenBalance >= 0 && balance + givenBalance <= mxLen
                )
                {
                    add(count[used+1][len+1][balance+givenBalance], currCnt);
                }
            }
        }
    }
    return count[1][mxLen][0];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int curr, need;
    std::string s;
    while (std::cin >> need >> curr >> s) {
        std::cout << solve(curr, need, s) << std::endl;
    }
    return 0;
}