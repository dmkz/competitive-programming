/*
    Problem: 550A. Two Substrings
    
    Solution: implementation, strings, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

int main() {
    std::string s; 
    while (std::cin >> s) {
        const int n = (int)s.size();
        int fiAB = n, fiBA = n, seAB = -1, seBA = -1;
        for (int i = 0; i + 1 < n; ++i) {
            if (s[i] == 'A' && s[i+1] == 'B') {
                fiAB = std::min(fiAB,i+1);
                seAB = std::max(seAB,i);
            }
            if (s[i] == 'B' && s[i+1] == 'A') {
                fiBA = std::min(fiBA,i+1);
                seBA = std::max(seBA,i);
            }
        }
        std::cout << (fiBA < seAB || fiAB < seBA ? "YES" : "NO") << std::endl;
    }
    return 0;
}