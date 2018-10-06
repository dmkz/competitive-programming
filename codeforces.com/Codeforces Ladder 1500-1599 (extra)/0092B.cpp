/*
    Problem: 92B. Binary Number
    
    Solution: math, long addition, right shift, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::string s; std::cin >> s;
    s = "0" + s;
    int answ = 0;
    while (!(s == "01" || s == "1")) {
        if (s.back() == '1') {
            int p = (int)s.size()-1;
            while (s[p] == '1') {
                s[p--] = '0';
            }
            s[p] = '1';
            ++answ;
        } else {
            s.pop_back();
            ++answ;
        }
    }
    std::cout << answ;
    return 0;
}