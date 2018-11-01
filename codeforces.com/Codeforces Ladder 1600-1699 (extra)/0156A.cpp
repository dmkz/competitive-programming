/*
    Problem: 156A. Message
    
    Solution: dynamic programming, prefix sums, O(n*m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int solve(std::string s, std::string t) {
    const int n = (int)s.size(), m = (int)t.size();
    s = "$" + s;
    t = "^" + t;
    static int equal[2048][2048], sdiag[2048][2048];
    std::fill(&equal[0][0], &equal[0][0]+2048*2048,0);
    std::fill(&sdiag[0][0], &sdiag[0][0]+2048*2048,0);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            equal[i][j] = (s[i] == t[j]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            sdiag[i+1][j+1] = equal[i][j] + sdiag[i][j];
        }
    }
    int answ = m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int len = std::min(n-i+1, m-j+1);
            int nOp = m - (sdiag[i+len][j+len]-sdiag[i][j]);
            answ = std::min(answ, nOp);
        }
    }
    return answ;
}

int main() {
    std::string s, t;
    while (std::cin >> s >> t) {
        std::cout << solve(s, t) << std::endl;
    }
    return 0;
}