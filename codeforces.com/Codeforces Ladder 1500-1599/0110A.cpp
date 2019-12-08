/*
    Problem: 110A. Nearly Lucky Number
    Solution: implementation
*/
#include <iostream>
#include <string>

bool is_lucky_number(int n) {
    do {
        if (n % 10 != 4 && n % 10 != 7) return false;
        n /= 10;
    } while (n > 0);
    return true;
}

int main() {
    std::string s;
    std::cin >> s;
    int n = 0;
    for (auto& it : s) {
        n += (it == '4' || it == '7');
    }
    std::cout << (is_lucky_number(n) ? "YES" : "NO");
    return 0;
}