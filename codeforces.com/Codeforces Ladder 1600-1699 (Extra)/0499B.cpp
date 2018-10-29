/*
    Problem: 499B. Lecture
    
    Solution: strings, implementation, std::map, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <map>

std::string choose(std::string& a, std::string& b) {
    if (a.size() < b.size()) return a;
    if (a.size() > b.size()) return b;
    return a;
}

int main() {
    int nText, nWords;
    while (std::cin >> nText >> nWords) {
        std::map<std::string, std::string> toChange;
        while (nWords--) {
            std::string s, t;
            std::cin >> s >> t;
            toChange[s] = choose(s,t);
        }
        while (nText--) {
            std::string s; std::cin >> s;
            std::cout << toChange[s] << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}