/*
    Problem: 56A. Bar
    
    Solution: strings, implementation, O(n * max|s|)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int main() {
    int n;
    std::vector<std::string> alcohol = {"ABSINTH","BEER","BRANDY","CHAMPAGNE","GIN","RUM","SAKE","TEQUILA","VODKA","WHISKEY","WINE"};
    while (std::cin >> n) {
        std::string s; int answ = 0;
        for (int i = 0; i < n; ++i) {
            std::cin >> s;
            if ('0' <= s[0] && s[0] <= '9') {
                answ += std::stoi(s) < 18;
            } else {
                answ += std::find(alcohol.begin(), alcohol.end(), s) != alcohol.end();
            }
        }
        std::cout << answ << std::endl;
    }
    return 0;
}

