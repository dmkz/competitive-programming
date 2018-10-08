/*
    Problem: 437A. The Child and Homework
    
    Solution: implementation, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::vector<std::string> arr(4);
    for (auto& it : arr) {
        std::cin >> it;
        it = it.substr(it.find('.')+1);
    }
    char c1 = '?';
    for (int i = 0; i < 4; ++i) {
        bool flag = true;
        for (int j = 0; j < 4; ++j) {
            if (i == j) continue;
            if (2*arr[i].size() > arr[j].size()) {
                flag = false;
                break;
            }
        }
        if (flag) {
            c1 = char('A'+i);
        }
    }
    char c2 = '?';
    for (int i = 0; i < 4; ++i) {
        bool flag = true;
        for (int j = 0; j < 4; ++j) {
            if (i == j) continue;
            if (arr[i].size() < 2*arr[j].size()) {
                flag = false;
                break;
            }
        }
        if (flag) {
            c2 = char('A'+i);
        }
    }
    
    if (c1 == '?') {
        if (c2 == '?') {
            std::cout << 'C';
        } else {
            std::cout << c2;
        }
    } else {
        if (c2 == '?') {
            std::cout << c1; 
        } else {
            std::cout << 'C';
        }
    }
    return 0;
}