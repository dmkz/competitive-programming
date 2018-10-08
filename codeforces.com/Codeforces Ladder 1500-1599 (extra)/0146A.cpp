/*
    Problem: 146A. Lucky Ticket
    
    Solution: implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

int main() {
    int n; std::string s; std::cin >> n >> s;
    for (auto it : s) {
        if (!(it == '4' || it == '7')) {
            std::cout << "NO";
            return 0;
        }
    }
    int sum = 0;
    for (int i = 0; i < n / 2; ++i) {
        sum += (s[i] - '0');
    }
    for (int i = n / 2; i < n; ++i) {
        sum -= (s[i] - '0');
    }
    std::cout << (sum == 0 ? "YES" : "NO");
    return 0;
}