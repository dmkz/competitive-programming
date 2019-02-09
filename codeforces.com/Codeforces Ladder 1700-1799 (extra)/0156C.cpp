/*
    Problem: 156C. Cipher
    
    Solution: dynamic programming, O((26*n)^2+t*n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>

namespace Solution {
    
    const int mod = (int)1e9+7;
    
    int& addto(int& a, int b) { return (a += b) >= mod ? (a -= mod) : a; }
    
    std::vector<std::vector<int>> countSequences;
    
    void precalc(const int MXLEN) {
        countSequences.assign(MXLEN+1, std::vector<int>(MXLEN * 26, 0));
        // countSequences[len][sum] -> number of sequences with length = len and sum of items = sum
        countSequences[0][0] = 1;
        for (int currLen = 0; currLen < MXLEN; ++currLen) {
            for (int newDigit = 0; newDigit < 26; ++newDigit) {
                for (int currSum = 0; currSum + newDigit < MXLEN * 26; ++currSum) {
                    addto(countSequences[currLen+1][currSum + newDigit], countSequences[currLen][currSum]);
                }
            }
        }
    }
    
    int getAnswer(const int len, const int sum) {
        return (countSequences[len][sum]-1+mod)%mod;
    }
}

int main() {
    Solution::precalc(100);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cerr.tie(0); std::cout.tie(0);
    int t;
    while (std::cin >> t) {
        while (t--) {
            std::string s; std::cin >> s;
            int sum = 0;
            for (int i = 0; i < (int)s.size(); ++i) {
                sum += (s[i] - 'a');
            }
            std::cout << Solution::getAnswer((int)s.size(), sum) << "\n";
        }
        std::cout << std::endl;
    }
    return 0;
}