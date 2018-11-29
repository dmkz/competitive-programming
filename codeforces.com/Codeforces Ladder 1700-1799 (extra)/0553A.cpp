/*
    Problem: 553A. Kyoya and Colored Balls
    
    Solution: combinatorics, math, number theory, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <numeric>

const int mod = (int)1e9+7;

int& addto(int& a, int b) {
    return (a += b) >= mod ? (a -= mod) : a;
}

int add(int a, int b) {
    return addto(a,b);
}

int mul(int a, int b) {
    return int(1LL * a * b % mod);
}

const int NMAX = 1001;
int bin[NMAX][NMAX];

void precalc() {
    bin[0][0] = 1;
    for (int n = 1; n < NMAX; ++n) {
        bin[n][n] = bin[n][0] = 1;
        for (int k = 1; k < n; ++k) {
            bin[n][k] = add(bin[n-1][k-1], bin[n-1][k]);
        }
    }
}

int solve(std::vector<int>& arr, int sum) {
    if (arr.empty()) {
        return 1;
    }
    int coeff = bin[sum-1][arr.back()-1];
    sum -= arr.back();
    arr.pop_back();
    return mul(coeff, solve(arr,sum));
}

int main() {
    precalc();
    int n;
    while (std::cin >> n) {
        std::vector<int> arr(n);
        for (auto& it : arr) { std::cin >> it; }
        std::cout << solve(arr, std::accumulate(arr.begin(), arr.end(), 0)) << std::endl;
    }
    return 0;
}