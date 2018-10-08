/*
    Problem: 284B. Cows and Poker Game
    
    Solution: implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

int main() {
    int n; std::cin >> n;
    std::string s; std::cin >> s;
    int nI = 0, answ = 0; 
    for (auto& it : s) {
        nI += (it == 'I');
    }
    for (auto& it : s) {
        answ += (it != 'F') && (nI - (it == 'I') == 0);
    }
    std::cout << answ;
    return 0;
}