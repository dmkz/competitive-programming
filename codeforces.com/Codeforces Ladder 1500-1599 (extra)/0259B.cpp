/*
    Problem: 259B. Little Elephant and Magic Square
    
    Solution: brute force, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
const int AMAX = (int)1e5;
int main() {
    int a[4][4];
    for (int i = 1; i < 4; ++i) {
        for (int j = 1; j < 4; ++j) {
            std::cin >> a[i][j];
        }
    }
    for (int a11 = 1; a11 <= AMAX; ++a11) {
        int s = a11 + a[1][2] + a[1][3];
        int a22 = s - a[2][1] - a[2][3];
        int a33 = s - a[3][1] - a[3][2];
        if (a22 < 1 || a22 > AMAX) continue;
        if (a33 < 1 || a33 > AMAX) continue;
        a[1][1] = a11;
        a[2][2] = a22;
        a[3][3] = a33;
        bool flag = true;
        for (int i = 1; i <= 3; ++i) {
            int s1 = 0;
            for (int j = 1; j <= 3; ++j) {
                s1 += a[i][j];
            }
            if (s1 != s) { flag = false; break; }
        }
        for (int j = 1; j <= 3; ++j) {
            int s1 = 0;
            for (int i = 1; i <= 3; ++i) {
                s1 += a[i][j];
            }
            if (s1 != s) { flag = false; break; }
        }
        int s1 = 0;
        for (int i = 1; i <= 3; ++i) {
            s1 += a[i][i];
        }
        int s2 = 0;
        for (int i = 1; i <= 3; ++i) {
            s2 += a[i][4-i];
        }
        if (s1 != s) flag = false;
        if (s2 != s) flag = false;
        if (flag) {
            break;
        }
    }
    for (int i = 1; i < 4; ++i) {
        for (int j = 1; j < 4; ++j) {
            std::cout << a[i][j] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}