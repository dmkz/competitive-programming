/*
    Problem: 625B. War of the Corporations
    
    Solution: strings, greedy, O(30*n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

int solve(std::string s, std::string t) {
    int answ = 0;
    for (int i = 0; i + (int)t.size() <= (int)s.size(); ++i) {
        if (s.substr(i, (int)t.size()) == t) {
            answ++;
            s[i+(int)t.size()-1] = '#';
        }
    }
    return answ;
}

int main() {
    std::string s, t;
    while (std::cin >> s >> t) {
        std::cout << solve(s, t) << std::endl;
    }
    return 0;
}