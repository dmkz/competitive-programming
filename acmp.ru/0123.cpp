#include <iostream>
#include <functional>

int main() {
    std::string s; std::cin >> s;
    static int count[81][81]; // [len][balance]
    count[0][0] = 1;
    for (int n = 0; n < (int)s.size(); ++n) {
        for (int b = 0; b <= (int)s.size(); ++b) {
            if (s[n] == '?' || s[n] == '(') count[n+1][b+1] += count[n][b];
            if ((s[n] == '?' || s[n] == ')') && b > 0) count[n+1][b-1] += count[n][b];
        }
    }
    std::cout << count[s.size()][0];
    return 0;
}