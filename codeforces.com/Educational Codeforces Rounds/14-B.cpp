/*
    Problem: 691B. s-palindrome
    
    Solution: implementation, strings, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::string s;
    std::cin >> s;
    std::vector<char> rev(256, -1);
    rev['A'] = 'A';
    rev['b'] = 'd';
    rev['d'] = 'b';
    rev['p'] = 'q';
    rev['q'] = 'p';
    rev['H'] = 'H';
    rev['I'] = 'I';
    rev['M'] = 'M';
    rev['O'] = 'O';
    rev['o'] = 'o';    
    rev['T'] = 'T';
    rev['U'] = 'U';
    rev['V'] = 'V';
    rev['v'] = 'v';
    rev['w'] = 'w';
    rev['W'] = 'W';
    rev['X'] = 'X';
    rev['x'] = 'x';
    rev['Y'] = 'Y';
    for (int i = 0, j = (int)s.size()-1; i <= j; ++i, --j) {
        if (rev[s[i]] != s[j]) {
            std::cout << "NIE";
            return 0;
        }
    }
    std::cout << "TAK";
    return 0;
}