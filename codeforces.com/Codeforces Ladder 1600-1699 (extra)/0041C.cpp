/*
    Problem: 41C. Email address
    
    Solution: strings, greedy, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

std::string solve(std::string s) {
    std::string tmp = "";
    for (int i = 0; i < (int)s.size(); ) {
        if (i + 3 < (int)s.size() && i != 0 && s.substr(i, 3) == "dot") {
            tmp.push_back('.');
            i += 3;
        } else {
            tmp.push_back(s[i]);
            ++i;
        }
    }
    s = tmp;
    for (int i = 1; i + 2 < (int)s.size(); ++i) {
        if (s.substr(i, 2) == "at") {
            auto t = s.substr(0, i) + "@" + s.substr(i+2);
            if (t.size() < tmp.size()) {
                tmp = t;
            } else if (t.size() == tmp.size() && t < tmp) {
                tmp = t;
            }
        }
    }
    return tmp;
}

int main() {
    std::string s;
    while (std::cin >> s) {
        std::cout << solve(s) << std::endl;
    }
    return 0;
}