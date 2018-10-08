/*
    Problem: 427B. Prison Transfer
    
    Solution: Sparse Table, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>

const int PMAX = 18, NMAX = 256*1024;

int main() {
    int n, count, limit; 
    std::cin >> n >> limit >> count;
    static int max[PMAX][NMAX];
    for (int i = 0; i < n; ++i) {
        std::cin >> max[0][i];
    }
    for (int p = 1; p < PMAX; ++p) {
        for (int i = 0; i + (1 << p) - 1 < n; ++i) {
            max[p][i] = std::max(max[p-1][i], max[p-1][i + (1 << (p-1))]);
        }
    }
    int pow = 0;
    while ((1 << (pow+1)) <= count) ++pow;
    int answ = 0;
    for (int i = 0; i + count - 1 < n; ++i) {
        int mx = std::max(max[pow][i], max[pow][i + count - (1 << pow)]);
        answ += (mx <= limit);
    }
    std::cout << answ;
    return 0;
}