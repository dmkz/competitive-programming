/*
    Problem: 818E. Card Game Again
    
    Solution: Sparse Table, binary lifting, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <functional>
#include <cassert>

typedef long long ll;

int main() {
    // Precalculate binary log:
    const int PMAX = 17, NMAX = 128*1024;
    static int log2[1+NMAX];
    for (int i = 2; i <= NMAX; ++i) {
        log2[i] = log2[i/2]+1;
    }
    static int mul[1+PMAX][1+NMAX]; // Sparse Table for multiplication modulo k
    // Input:
    int n, k; scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i) {
        int value; scanf("%d", &value);
        mul[0][i] = value % k;
    }   
    // Fill sparse table:
    for (int p = 1; p < PMAX; ++p) {
        for (int i = 0; i + (1 << p)-1 < n; ++i) {
            mul[p][i] = int(ll(mul[p-1][i]) * mul[p-1][i+(1 << (p-1))] % k);
        }
    }
    // Function for getting leftmost position that arr[pos] * arr[pos+1] * ... * arr[left] % k = 0
    // using binary lifting technique:
    std::function<int(int,int&)> get_left = [&](int pos, int& prod) {
        prod = 1;
        for (int pow = PMAX-1; pow >= 0; --pow) {
            if (pos + (1 << pow) < n && 1LL * prod * mul[pow][pos] % k != 0) {
                prod = int(1LL * prod * mul[pow][pos] % k);
                pos += 1 << pow;
            }
        }
        return pos;
    };
    
    // Calculate answer:
    ll answ = 0;
    for (int i = 0; i < n; ++i) {
        int left, prod;
        left = get_left(i, prod);
        assert(prod != 0);
        if (1LL * prod * mul[0][left] % k == 0) {
            answ += std::max(0, n - left);
        }
    }
    std::cout << answ;
    return 0;
}