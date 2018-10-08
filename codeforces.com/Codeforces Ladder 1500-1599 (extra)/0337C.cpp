/*
    Problem: 337C. Quiz
    
    Solution: number theory, math, O(log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <algorithm>

const int mod = (int)1e9+9;

int pow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) {
            res = int(1LL * res * a % mod);
        }
        a = int(1LL * a * a % mod);
        n >>= 1;
    }
    return res;
}

int main() {
    int n, m, k;
    while (scanf("%d %d %d", &n, &m, &k) == 3) {
        if (m <= n / k * (k-1) + n % k) {
            printf("%d\n", m);
            continue;
        }
        int nAdd = m - n / k * (k-1) - n % k;
        int score = int(((pow(2, nAdd+1)-2LL+mod) * k + m - k * nAdd) % mod);
        printf("%d\n", score);
    }
    return 0;
}