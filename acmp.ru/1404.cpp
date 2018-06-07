#include <iostream>
#include <string>

int main() {
    std::string s;
    std::cin >> s;
    for (auto& it : s) {
        it = (it - 'a' + 1) % 26 + 'a';
    }
    std::cout << s;
    return 0;
}