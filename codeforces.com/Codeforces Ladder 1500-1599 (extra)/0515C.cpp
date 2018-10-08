/*
    Problem: 515C. Drazil and Factorial
    
    Solution: math, greedy, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>

int main() {
    int n; std::cin >> n;
    std::string s; std::cin >> s;
    std::string t;
    for (auto& it : s) {
        if (it == '2' || it == '3' || it == '7' || it == '5') t.push_back(it);
        if (it == '4') t.push_back('2'), t.push_back('2'), t.push_back('3');
        if (it == '6') t.push_back('5'), t.push_back('3');
        if (it == '8') t.push_back('2'), t.push_back('2'), t.push_back('2'), t.push_back('7');
        if (it == '9') t.push_back('3'), t.push_back('3'), t.push_back('2'), t.push_back('7');
    }
    std::sort(t.begin(), t.end());
    std::reverse(t.begin(), t.end());
    std::cout << t;
    return 0;
}