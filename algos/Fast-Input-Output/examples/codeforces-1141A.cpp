#include <bits/stdc++.h>
#include "FastIO.hpp"

int main() {
    FastIO::Reader fin;
    FastIO::Writer fout;
    for (int n, m; fin >> n >> m; ) {
        int answ = -1;
        if (m % n == 0) {
            int div = m / n;
            int pow2 = 0, pow3 = 0;
            while (div > 0 && div % 3 == 0) { div /= 3; pow3++; }
            while (div > 0 && div % 2 == 0) { div /= 2; pow2++; }
            if (div == 1) {
                answ = pow2+pow3;
            }
        }
        fout << answ << '\n';
    }
    return 0;
}