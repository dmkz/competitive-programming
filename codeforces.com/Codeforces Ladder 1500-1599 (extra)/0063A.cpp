/*
    Problem: 63A. Sinking Ship
    
    Solution: implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

int order(const std::string& s) {
    if (s == "rat") return 0;
    if (s == "woman" || s == "child") return 1;
    if (s == "man") return 2;
    assert(s == "captain");
    return 3;
}

int main() {
    int n; std::cin >> n;
    std::vector<std::string> name(n);
    std::vector<int> type(n);
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> name[i] >> s;
        type[i] = order(s);
    }
    for (int t = 0; t <= 3; ++t) {
        for (int i = 0; i < n; ++i) {
            if (type[i] == t) {
                std::cout << name[i] << '\n';
            }
        }
    }
    return 0;
}