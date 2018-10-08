/*
    Problem: 312A. Whose sentence is it?
    
    Solution: strings, implementation, O(n*MAX)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>

int main() {
    int n; std::string s; std::cin >> n;
    std::getline(std::cin, s);
    while (n--) {
        std::getline(std::cin, s);
        bool f1 = (s.find("miao.") == 0);
        std::string r = s;
        std::reverse(r.begin(), r.end());
        bool f2 = (r.find(".alal") == 0);
        if (f1 && f2 || !f1 && !f2) {
            std::cout << "OMG>.< I don't know!\n";
        } else if (f1) {
            std::cout << "Rainbow's\n"; 
        } else {
            std::cout << "Freda's\n";
        }
    }
    return 0;
}