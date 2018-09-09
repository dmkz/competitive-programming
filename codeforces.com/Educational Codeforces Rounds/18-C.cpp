/*
    Problem: 792C. Divide by Three
    
    Solution: greedy, math, number theory, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>

typedef long long ll;

std::string try_to_erase(std::string s, int count, int digit1, int digit2, int digit3) {
    int pos = (int)s.size()-1;
    while (count > 0) {
        while (pos >= 0 && !(s[pos] - '0' == digit1 || s[pos] - '0' == digit2 || s[pos]-'0' == digit3)) {
            --pos;
        }
        if (pos < 0) break;
        --count;
        s.erase(s.begin() + pos);
        --pos;
    }
    int len = 0;
    while (len < (int)s.size() && s[len] == '0') ++len;
    s = s.substr(len);
    if (count > 0) return "-1";
    if (len > 0 && s.empty()) s = "0";
    if (s.empty()) return "-1";
    return s;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::string s; std::cin >> s;
    
    int sum = 0;
    for (auto& it : s) sum += (it - '0');
    
    if (sum % 3 == 0) {
        std::cout << s; return 0;
    }
    
    if (sum % 3 == 1) { // one digit in {1, 4, 7}, or one digit in {2, 5, 8}
        std::string t1 = try_to_erase(s, 1, 1, 4, 7);
        std::string t2 = try_to_erase(s, 2, 2, 5, 8);
        if (t1 == "-1" && t2 == "-1") {
            std::cout << "-1";
        } else if (t1 == "-1") {
            std::cout << t2;
        } else if (t2 == "-1") {
            std::cout << t1;
        } else {
            std::cout << (t1.size() < t2.size() ? t2 : t1);
        }
    } else { // two digits in {1, 4, 7}, or one digit in {2, 5, 7}
        std::string t1 = try_to_erase(s, 2, 1, 4, 7);
        std::string t2 = try_to_erase(s, 1, 2, 5, 8);
        if (t1 == "-1" && t2 == "-1") {
            std::cout << "-1";
        } else if (t1 == "-1") {
            std::cout << t2;
        } else if (t2 == "-1") {
            std::cout << t1;
        } else {
            std::cout << (t1.size() < t2.size() ? t2 : t1);
        }
    }
    
    
    return 0;
}