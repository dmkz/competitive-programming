/*
    Problem: 258A. Little Elephant and Bits
    Solution: greedy, math
*/
#include <iostream>
#include <string>

int main() {
    std::string s; std::cin >> s;
    int p = std::max((int)s.find('0'), 0);
    std::cout << s.substr(0, p) + s.substr(p+1);
    return 0;
}