/*
    Problem: 154A. Hometask
    
    Solution: greedy, strings, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>

struct Pair {
    char fi, se;
};

int main() {
    std::string s;
    while (std::cin >> s) {
        s = "?" + s + "?";
        std::vector<char> pairWith(256);
        int nPairs; std::cin >> nPairs;
        while (nPairs--) {
            std::string tmp; std::cin >> tmp;
            char fi = tmp[0], se = tmp[1];
            pairWith[fi] = se;
            pairWith[se] = fi;
        }
        int p = 1, answ = 0;
        while (p+1 < (int)s.size()) {
            char fi = s[p], se = pairWith[s[p]];
            int nFi = 0, nSe = 0, r = p;
            while (s[r] == fi || s[r] == se) {
                nFi += (s[r] == fi);
                nSe += (s[r] == se);
                ++r;
            }
            answ += std::min(nFi, nSe);
            p = r;
        }
        std::cout << answ << std::endl;
    }
    return 0;
}