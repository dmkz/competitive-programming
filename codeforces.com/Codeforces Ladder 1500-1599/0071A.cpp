/*
    Problem: 71A. Way Too Long Words
    Solution: strings
*/
#include <iostream>
#include <string>

int main() {
    int n; std::cin >> n;
    while (n--) {
        std::string s; std::cin >> s;
        if (s.size() > 10u) {
            s = s.front() + std::to_string(s.size()-2u) + s.back();
        }
        std::cout << s << '\n';
    }
    return 0;
}