/*
    Problem: 435C. Cardiogram
    
    Solution: implementation, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::vector<std::string> field(2001, std::string(2001, ' '));
    int row = 1000, col = 0;
    int n, sum = 0; std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int a; std::cin >> a;
        sum += a;
        while (a--) {
            field[row][col] = i % 2 == 0 ? '/' : '\\';
            row += i % 2 == 0 ? -1 : 1;
            col++;
        }
        if (i % 2 == 0) {
            ++row;
        } else --row;
    }
    std::vector<std::string> answer;
    for (row = 0; row < 2001; ++row) {
        if (field[row] == std::string(2001, ' ')) {
            continue;
        }
        answer.push_back(field[row]);
        answer.back().resize(sum);
    }
    for (auto& it : answer) {
        std::cout << it << '\n';
    }
    return 0;
}