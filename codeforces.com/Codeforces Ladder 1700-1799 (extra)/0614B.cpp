/*
    Problem: 614B. Gena's Code
    
    Solution: strings, number theory, implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <cassert>

int get_power_10(std::string& s) {
    int answ = 0;
    while (s.back() == '0') {
        answ++, s.pop_back();
    }
    return answ;
}

int main() {
    int n;
    while (std::cin >> n) {
        bool was_zero = false;
        int cntZeros = 0;
        std::string number = "";
        for (int i = 0; i < n; ++i) {
            std::string s; std::cin >> s;
            was_zero = was_zero || (s == "0");
            int pow = get_power_10(s);
            cntZeros += pow;
            if (s != "1") {
                assert(number == "");
                number = s;
            }
        }
        if (number.empty()) {
            number = "1";
        }
        if (was_zero) {
            std::cout << "0" << std::endl;
        } else {
            number += std::string(cntZeros, '0');
            std::cout << number << std::endl;
        }
    }
    return 0;
}