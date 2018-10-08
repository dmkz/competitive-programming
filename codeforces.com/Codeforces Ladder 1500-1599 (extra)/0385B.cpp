/*
    Problem: 385B. Bear and Strings
    
    Solution: strings, two pointers, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

typedef long long ll;
int main() {
    std::string s; std::cin >> s; int n = (int)s.size();
    int l = 0, r = -1;
    ll answ = ll(n) * (n+1)/2;
    while (l < n) {
        while (r+1 < n && (r+1-l+1 < 4 || s.substr(r-2, 4) != "bear")) {
            ++r;
        }
        answ -= r-l+1;
        ++l;
    }
    std::cout << answ;
    return 0;
}