/*
    Problem: 133B. Unary
    
    Solution: math, long remainder, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::string s; std::cin >> s;
    std::string t;
    for (auto it : s) {
        if (it == '>') t += "1000";
        if (it == '<') t += "1001";
        if (it == '+') t += "1010";
        if (it == '-') t += "1011";
        if (it == '.') t += "1100";
        if (it == ',') t += "1101";
        if (it == '[') t += "1110";
        if (it == ']') t += "1111";
    }
    int res = 0; const int mod = (int)1e6+3;
    for (auto & it : t) {
        res = (res * 2 + (it - '0')) % mod;
    }
    std::cout << res;
    return 0;
}