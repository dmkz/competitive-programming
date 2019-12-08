/*
    Problems: 96A. Football
    Solution: implementation, strings
*/
#include <iostream>
#include <string>

int main() {
    std::string s;
    std::cin >> s;
    std::cout << (
        s.find(std::string(7, '0')) != -1 || 
        s.find(std::string(7, '1')) != -1 ? "YES" : "NO");
    return 0;
}