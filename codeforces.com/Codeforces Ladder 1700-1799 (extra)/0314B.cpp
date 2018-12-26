/*
    Problem: 314B. Sereja and Periods
    
    Solution: strings, dynamic programming, O(|s|^2+n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

int solve(int q1, int q2, std::string s1, std::string s2) {
    const int SMAX = 111, n1 = (int)s1.size(), n2 = (int)s2.size();
    static int nMatched[SMAX][SMAX];
    std::fill(&nMatched[0][0], &nMatched[0][0]+SMAX * SMAX,0);
    for (int p1 = n1-1; p1 >= 0; --p1) {
        for (int p2 = n2-1; p2 >= 0; --p2) {
            if (s1[p1] == s2[p2]) {
                nMatched[p1][p2] = nMatched[p1+1][(p2+1) % n2]+1;
            } else {
                nMatched[p1][p2] = nMatched[p1+1][p2];
            }
        }
    }
    int p2 = 0, k2 = 0;
    for (int cnt = 0; cnt < q1; ++cnt) {
        int matched = nMatched[0][p2];
        k2 += (p2 + matched) / n2;
        p2 = (p2 + matched) % n2;
    }
    return k2 / q2;
}

int main() {
    int n1, n2; std::string s1, s2;
    while (std::cin >> n1 >> n2 >> s1 >> s2) {
        std::cout << solve(n1, n2, s1, s2) << std::endl;
    }
    return 0;
}