#include <iostream>

int main() {
    std::string s = "A";
    while (2 * s.size() <= 200000) {
        const int n = s.size();
        for (int i = 0; i < n; ++i) {
            s.push_back('B' - s[i] + 'A');
        }
    }
    return 0;
}