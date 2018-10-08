/*
    Problem: 382A. Ksenia and Pan Scales
    
    Solution: greedy, implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

int main() {
    std::string s; std::cin >> s;
    std::string fi = s.substr(0, s.find('|'));
    std::string se = s.substr(s.find('|')+1);
    std::string add; std::cin >> add;
    while (!add.empty()) {
        char c = add.back(); add.pop_back();
        if (se.size() < fi.size()) {
            se.push_back(c);
        } else {
            fi.push_back(c);
        }
    }
    if (fi.size() != se.size()) {
        std::cout << "Impossible";
    } else {
        std::cout << fi << "|" << se;
    }
    return 0;
}