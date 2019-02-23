/*
    Problem: 508E. Arthur and Brackets
    
    Solution: dynamic programming, O(n^3)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

namespace Solution {

    const int NMAX = 600;

    int n, l[NMAX], r[NMAX];

    int can[NMAX][NMAX], cnt[NMAX][NMAX], visited[NMAX][NMAX];
    
    void input() {
        std::cin >> n;
        for (int i = 0; i < n; ++i) {
            std::cin >> l[i] >> r[i];
        }
    }

    int solve(int low, int high) {
        if (low > high) {
            return 1;
        }
        if (visited[low][high]) {
            return can[low][high];
        }
        visited[low][high] = true;
        for (int k = 0; k < high - low + 1; ++k) {
            if (l[low] <= 2 * k + 1 && 2 * k + 1 <= r[low] && solve(low+1, low + k) && solve(low + k + 1, high)) {
                cnt[low][high] = k;
                can[low][high] = true;
                break;
            }
        }
        return can[low][high];
    }

    void getAnswer(std::string& s, int low, int high, int pos) {
        if (low > high) { return; }
        s[pos] = '(';
        const int k = cnt[low][high];
        s[pos + 2 * k + 1] = ')';
        getAnswer(s, low+1, low+k, pos+1);
        getAnswer(s, low+k+1, high, pos+2*k+2);
    }

    std::string solve() {
        if (!solve(0, n-1)) {
            return "IMPOSSIBLE";
        }
        std::string answ(2*n, '?');
        getAnswer(answ, 0, n-1, 0);
        return answ;
    }
}

int main() {
    Solution::input();
    std::cout << Solution::solve() << std::endl;
    return 0;
}