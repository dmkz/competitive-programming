/*
    Problem: 554B. Ohana Cleans Up
    
    Solution: implementation, brute force, O(n^3)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int solve(int row, std::vector<std::string> field) {
    int n = (int)field.size();
    for (int c = 0; c < n; ++c) {
        if (field[row][c] == '0') {
            for (int r = 0; r < n; ++r) {
                field[r][c] = char('1' - field[r][c] + '0');
            }
        }
    }
    int answ = 0;
    for (int r = 0; r < n; ++r) {
        bool flag = true;
        for (int c = 0; c < n; ++c) {
            if (field[r][c] == '0') {
                flag = false;
                break;
            }
        }
        answ += flag;
    }
    return answ;
}

int main() {
    int n; std::cin >> n;
    std::vector<std::string> field(n);
    for (auto& it : field) {
        std::cin >> it;
    }
    int answ = 0;
    for (int r = 0; r < n; ++r) {
        answ = std::max(answ, solve(r, field));
    }
    std::cout << answ;
    return 0;
}