/*
    Problem: 691C. Exponential notation
    
    Solution: implementation, strings, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <cassert>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::string s;
    std::cin >> s;
    s = '0' + s;
    
    int p = (int)s.find('.');
    if (p == -1) {
        int len = 0;
        while (s[len] == '0') ++len;
        s = s.substr(len);
        if (s.size() != 1u) {
            int pow = (int)s.size()-1;
            s.insert(s.begin()+1, '.');
            while (s.back() == '0') s.pop_back();
            if (s.back() == '.') s.pop_back();
            s = s + "E" + std::to_string(pow);
            std::cout << s;
            return 0;
        }
        std::cout << s;
        return 0;        
    }
    
    while (s.back() == '0') {
        s.pop_back();
    }
    
    int pow = 0;
    s.push_back('0');
    int len = 0;
    while (s[len] == '0' && s[len+1] != '.') ++len;
    s = s.substr(len);
    p -= len;
    // 0.0000123 = 0.000123 / 10
    int pos = 0;
    while (s[pos] == '0') {
        ++pos;
        assert(s[pos] == '.');
        std::swap(s[pos], s[pos+1]);
        ++p;
        pow--;
    }
    len = 0;
    while (s[len] == '0' && s[len+1] != '.') ++len;
    s = s.substr(len);
    p -= len;
    assert(s[p] == '.');
    while (p != 1) {
        std::swap(s[p-1], s[p]);
        --p;
        pow++;
    }
    while (s.back() == '0') s.pop_back();
    if (s.back() == '.') s.pop_back();
    std::cout << s;
    if (pow != 0) {
        std::cout << "E" + std::to_string(pow);
    }
    return 0;
}