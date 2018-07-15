#include <iostream>
#include <string>
#include <algorithm>

bool is_palindromic(int number) {
    std::string s;
    do {
        s.push_back(char(number % 10 + '0'));
        number /= 10;
    } while (number > 0);
    
    for (int i = 0, j = (int)s.size()-1; i <= j; ++i, --j) {
        if (s[i] != s[j]) {
            return false;
        }
    }
    
    return true;
}

int main() {
    int answer = 0;
    for (int a = 100; a <= 999; ++a) {
        for (int b = 100; b <= 999; ++b) {
            if (is_palindromic(a*b)) {
                answer = std::max(answer, a*b);
            }
        }
    }
    std::cout << answer;
    return 0;
}