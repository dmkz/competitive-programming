/*
    Problem: 196A. Lexicographically Maximum Subsequence
    
    Solution: strings, dynamic programming, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

std::string lexMaxSubseq(const std::string& s) {
    std::string answ;
    const int n = (int)s.size();
    std::vector<int> next(n, n-1);
    char max = *std::max_element(s.begin(), s.end());
    for (int i = n-2; i >= 0; --i) {
        if (s[i+1] >= s[next[i+1]]) {
            next[i] = i+1;
        } else {
            next[i] = next[i+1];
        }
    }
    int curr = 0;
    if (s[0] != max) {
        curr = next[0];
    }
    while (true) {
        answ += s[curr];
        int prev = curr;
        curr = next[curr];
        if (curr == prev) {
            break;
        }
    }
    return answ;
}

int main() {
    std::string s;
    while (std::cin >> s) {
        std::cout << lexMaxSubseq(s) << std::endl;
    }
    return 0;
}

