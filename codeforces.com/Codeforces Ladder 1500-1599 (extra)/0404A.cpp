/*
    Problem: 404A. Valera and X
    
    Solution: implementation, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

int main() {
    int n; std::cin >> n; char in = -1, out = -1;
    for (int i = 0; i < n; ++i) {
        std::string s; std::cin >> s;
        for (int j = 0; j < n; ++j) {
            if (i == j || i == n - j - 1) {
                if (in == -1) in = s[j];
                if (s[j] != in) {
                    std::cout << "NO";
                    return 0;
                }
            } else {
                if (out == -1) out = s[j];
                if (s[j] != out) {
                    std::cout << "NO";
                    return 0;
                }
            }
        }
    }
    std::cout << (in == out ? "NO" : "YES");
    return 0;
}