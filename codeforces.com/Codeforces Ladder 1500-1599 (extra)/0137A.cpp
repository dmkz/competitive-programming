/*
    Problem: 137A. Postcards and photos
    
    Solution: implementation, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

int main() {
    int answ = 0;
    std::string s; std::cin >> s;
    while (!s.empty()) {
        int i;
        for (i = 0; i < std::min(5, (int)s.size()); ++i) {
            if (s[i] != s[0]) {
                break;
            }
        }
        answ++;
        s = s.substr(i);
    }
    std::cout << answ;
    return 0;
}