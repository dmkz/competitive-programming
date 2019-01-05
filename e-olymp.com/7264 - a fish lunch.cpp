/*
    Problem: 7264. A fish lunch
    
    Solution: dynamic programming, probability theory, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <vector>

typedef long double ld;

int main() {
    std::cout << std::fixed << std::setprecision(7);
    int n, nM, nF, place, proc;
    while (std::cin >> n >> nM >> nF >> place >> proc) {
        ld p = ld(proc) / 100;
        std::vector<std::vector<ld>> prob(1+nM, std::vector<ld>(1+nF));
        prob[0][0] = 1;
        for (int nm = 0; nm <= nM; ++nm) {
            for (int nf = 0; nf <= nF; ++nf) {
                if (nm + nf >= n) continue;
                // next wish will be fish:
                if (nf+1 <= nF) {
                    ld coeff = (nm < nM) ? p : ld(1);
                    prob[nm][nf+1] += coeff * prob[nm][nf];
                }
                // next wish will be meat:
                if (nm+1 <= nM) {
                    ld coeff = (nm < nM) ? (1 - p) : ld(0);
                    prob[nm+1][nf] += coeff * prob[nm][nf];
                }
            }
        }
        ld answ = 0;
        for (int nm = 0; nm <= nM; ++nm) {
            for (int nf = 0; nf < nF; ++nf) {
                answ += (nm + nf + 1 == place) * prob[nm][nf];
            }
        }
        std::cout << answ << std::endl;
    }
    return 0;
}