/*
    Problem: 7263. A full set
    
    Solution: dynamic programming, probability theory, expected value, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>

typedef long double ld;

int main() {
    std::cout << std::fixed << std::setprecision(7);
    // Precalculation of C(n, k):
    const int NMAX = 1000;
    std::vector<std::vector<ld>> C(1+NMAX, std::vector<ld>(1+NMAX));
    C[0][0] = C[1][0] = C[1][1] = 1;
    for (int n = 2; n <= NMAX; ++n) {
        for (int k = 0; k <= n; ++k) {
            C[n][k] = C[n-1][k] + (k > 0 ? C[n-1][k-1] : ld(0));            
        }
    }
    int n, k;
    while (std::cin >> n >> k) {
        // Solution with dynamic programming technique:
        std::vector<ld> expected(1+n); // expected[nNotTaken] - expected number of shuffles
        for (int nNotTaken = 1; nNotTaken <= n; ++nNotTaken) {
            ld sum = 0;
            // how much we will take?
            for (int take = 1; take <= std::min(nNotTaken, k); ++take) {
                ld coeff = C[nNotTaken][take] * C[n - nNotTaken][k - take] / C[n][k];
                sum += coeff * (expected[nNotTaken-take] + 1);
            }
            ld coeff = C[nNotTaken][0] * C[n-nNotTaken][k] / C[n][k];
            expected[nNotTaken] = (sum + coeff) / (1 - coeff);
        }
        std::cout << expected[n] << std::endl;
    }
    return 0;
}