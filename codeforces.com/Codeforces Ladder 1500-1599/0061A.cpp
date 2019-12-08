/*
    Problem: 61A. Ultra-Fast Mathematician
    Solution: implementation
*/
#include <iostream>
#include <string>

int main() {
    std::string a, b;
    std::cin >> a >> b;
    std::string c = a;
    for (int i = 0; i < (int)c.size(); ++i) {
        c[i] = (b[i] - '0') ^ (c[i] - '0') + '0';
    }
    std::cout << c;
    return 0;
}