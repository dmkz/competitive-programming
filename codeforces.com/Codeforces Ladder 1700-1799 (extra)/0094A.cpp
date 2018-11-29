/*
    Problem: 94A. Restoring Password
    
    Solution: strings, implementation, O(10 * |s|)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
    std::string s;
    while (std::cin >> s) {
        std::vector<std::string> digits(10);
        for (int i = 0; i < 10; ++i) {
            std::cin >> digits[i];
        }
        std::string answ;
        for (int i = 0; i < 8; ++i) {
            std::string tmp = s.substr(10*i,10);
            for (int d = 0; d < 10; ++d) {
                if (tmp == digits[d]) {
                    answ.push_back(char(d+'0'));
                    break;
                }
            }
        }
        std::cout << answ << std::endl;
    }
    return 0;
}