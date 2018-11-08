/*
    Problem: 329A. Purification
    
    Solution: greedy, constructive, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>

typedef std::vector<std::string> vs;

int findEmptyCol(const vs& arr, int row) {
    for (int i = 0; i < (int)arr[row].size(); ++i) {
        if (arr[row][i] == '.') {
            return i;
        }
    }
    return -1;
}

int findEmptyRow(const vs& arr, int col) {
    for (int i = 0; i < (int)arr.size(); ++i) {
        if (arr[i][col] == '.') {
            return i;
        }
    }
    return -1;
}

struct Pair {
    int row, col;
};

int main() {
    int n;
    while (std::cin >> n) {
        vs arr(n);
        for (auto& it : arr) { std::cin >> it; }
        std::vector<Pair> answ;
        for (int r = 0; r < n; ++r) {
            int c = findEmptyCol(arr, r);
            if (c != -1) answ.push_back(Pair{r+1, c+1});
        }
        if ((int)answ.size() == n) {
            for (auto& it : answ) {
                std::cout << it.row << " " << it.col << "\n";
            }
            continue;
        }
        answ.clear();
        for (int c = 0; c < n; ++c) {
            int r = findEmptyRow(arr, c);
            if (r != -1) answ.push_back(Pair{r+1, c+1});
        }
        if ((int)answ.size() == n) {
            for (auto& it : answ) {
                std::cout << it.row << " " << it.col << "\n";
            }
            continue;
        }
        answ.clear();
        std::cout << -1 << std::endl;
    }
    return 0;
}