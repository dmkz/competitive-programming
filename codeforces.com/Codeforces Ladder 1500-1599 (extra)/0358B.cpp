/*
    Problem: 358B. Dima and Text Messages
    
    Solution: strings, subsequence, implementation, O(n + len)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

bool check(const std::string& a, const std::string& b) {
    int i = 0, j = 0; int n = (int)a.size(), m = (int)b.size();
    while (i < n && j < m) {
        if (a[i] == b[j]) ++i;
        ++j;
    }
    return i == n;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    std::string a, b; int n; std::cin >> n;
    a = "<3";
    while (n--) {
        std::string temp; std::cin >> temp;
        a += temp;
        a += "<3";
    }
    std::cin >> b;
    std::cout << (check(a, b) ? "yes" : "no");
    return 0;
}