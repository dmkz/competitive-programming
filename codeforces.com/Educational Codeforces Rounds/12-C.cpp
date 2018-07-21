/*
    Problem: 665C. Simple Strings
    
    Solutions: strings, greedy, O(n)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::string s;
    std::cin >> s;
    
    for (int i = 1; i < (int)s.size(); ++i) {
        if (s[i-1] == s[i]) {
            int c1 = s[i-1];
            int c2 = i+1 < (int)s.size() ? s[i+1] : '?';
            for (int c = 'a'; c <= 'z'; ++c) {
                if (c != c1 && c != c2) {
                    s[i] = c;
                    break;
                }
            }
        }
    }
    std::cout << s;
    return 0;
}