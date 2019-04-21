/*
    Problem: 59A. Word
    
    Solution: strings, implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
typedef std::pair<int,std::string> pis;
pis toupper(std::string s) {
    int ret = 0;
    for (auto &it : s) {
        if (std::islower(it)) {
            it = (char)std::toupper(it);
            ++ret;
        }
    }
    return pis(ret, s);
}
pis tolower(std::string s) {
    int ret = 0;
    for (auto &it : s) {
        if (std::isupper(it)) {
            it = (char)std::tolower(it);
            ++ret;
        }
    }
    return pis(ret, s);
}
int main() {
    std::string s;
    while (std::cin >> s) {
        auto p1 = tolower(s);
        auto p2 = toupper(s);
        if (p1.first <= p2.first) { std::cout << p1.second << std::endl; }
        else { std::cout << p2.second << std::endl; }
    }
    return 0;
}