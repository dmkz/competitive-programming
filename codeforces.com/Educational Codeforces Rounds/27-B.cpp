/*
    Problem: 845B. Luba And The Ticket
    
    Solution: brute force, O(10^len)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::string s; std::cin >> s;
    int min = 6;
    for (char c1 = '0'; c1 <= '9'; ++c1) {
        int op = (c1 != s[0]);
        for (char c2 = '0'; c2 <= '9'; ++c2) {
            op += (c2 != s[1]);
            for (char c3 = '0'; c3 <= '9'; ++c3) {
                op += (c3 != s[2]);
                int sum1 = c1-'0' + c2-'0' + c3-'0';
                for (char c4 = '0'; c4 <= '9'; ++c4) {
                    op += (c4 != s[3]);
                    for (char c5 = '0'; c5 <= '9'; ++c5) {
                        op += (c5 != s[4]);
                        for (char c6 = '0'; c6 <= '9'; ++c6) {
                            op += (c6 != s[5]);
                            int sum2 = c4-'0' + c5-'0' + c6-'0';
                            if (sum1 == sum2) {
                                min = std::min(op, min);
                            }
                            op -= (c6 != s[5]);
                        }
                        op -= (c5 != s[4]);
                    }
                    op -= (c4 != s[3]);
                }
                op -= (c3 != s[2]);
            }
            op -= (c2 != s[1]);
        }
    }
    std::cout << min;
    return 0;
}