/*
    Problem: 7269 - Probable diagnosis
    
    Solution: probability theory, O(n*m*k)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cassert>
#include <valarray>

using ld = long double;
using vd = std::vector<ld>;
using vvd = std::vector<vd>;

int main() {
    int nDiseases, nSymptoms, nPatients;
    while (scanf("%d %d", &nDiseases, &nSymptoms) == 2) {
        std::vector<ld> dis(1+nDiseases, 1);
        std::vector<std::vector<ld>> sym(1+nDiseases, std::vector<ld>(nSymptoms));
        for (int i = 0; i <= nDiseases; ++i) {
            if (i != 0) {
                scanf("%Lf", &dis[i]);
                dis[i] /= 100;
            }
            for (int j = 0; j < nSymptoms; ++j) {
                scanf("%Lf", &sym[i][j]);
                sym[i][j] /= 100;
            }
        }
        for (int i = 1; i <= nDiseases; ++i) { dis[0] -= dis[i]; }
        scanf("%d", &nPatients);
        char buf[201];
        std::string state;
        vd prob;
        while (nPatients--) {
            scanf("%200s", buf);
            state = buf;
            prob.assign(1+nDiseases, 1);
            ld denum = 0;
            for (int i = 0; i <= nDiseases; ++i) {
                for (int s = 0; s < nSymptoms; ++s) {
                    if (state[s] == '+') { prob[i] *= sym[i][s]; }
                    else if (state[s] == '-') { prob[i] *= (1 - sym[i][s]); }
                }
                denum += prob[i] * dis[i];
            }
            for (int i = 1; i <= nDiseases; ++i) {
                printf("%0.7Lf ", prob[i] * dis[i] / denum);
            }
            printf("\n");
        }
    }
    return 0;
}