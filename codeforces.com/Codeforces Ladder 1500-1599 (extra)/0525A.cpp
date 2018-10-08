/*
    Problem: 525A. Vitaliy and Pie
    
    Solution: implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
    int n, answ = 0; std::cin >> n;
    std::string s; std::cin >> s;
    std::vector<int> count(256);
    for (auto& it : s) {
        if ('a' <= it && it <= 'z') {
            count[it]++;
        } else {
            auto low = char(it - 'A' + 'a');
            if (count[low] == 0) {
                answ++;
            } else {
                count[low]--;
            }
        }
    }
    std::cout << answ;
    return 0;
}