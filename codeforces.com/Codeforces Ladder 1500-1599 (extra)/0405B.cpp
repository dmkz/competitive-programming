/*
    Problem: 405B. Domino Effect
    
    Solution: two pointers, implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

const bool debug = 0;

#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::string s; int n; std::cin >> n >> s;
    int rpos = -1, answ = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '.' && rpos == -1) {
            if (debug) {
                std::cout << "add 1 on " << i << std::endl;
            }
            answ++; continue;
        }
        if (s[i] == 'L') {
            if (rpos == -1) {
                if (debug) {
                    std::cout << "dec " << i << " on " << i << std::endl;
                }
                answ -= i;
            } else {
                if ((i - rpos + 1) % 2 == 1) {
                    if (debug) {
                        std::cout << "add 1 on " << (i + rpos+1)/2 << std::endl;
                    }
                    answ++;
                }
                rpos = -1;
            }
            continue;
        }
        if (s[i] == 'R') {
            rpos = i;
        }
    }
    std::cout << answ;
    return 0;
}