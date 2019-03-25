#include <bits/stdc++.h>
#include "FastIO.hpp"

int main() {
    FastIO::Reader fin;
    FastIO::Writer fout;
    for (int n; fin >> n; ) {
        std::vector<int> a(n);
        fin >> a;
        for (int i = n; i < 2 * n; ++i) {
            a.push_back(a[i-n]);
        }
        int answ = 0;
        for (int p = 0; p < (int)a.size(); ) {
            int r = p;
            while (r < (int)a.size() && a[r] == 1) { ++r; }
            answ = std::max(answ, r - p);
            p = r + 1;
        }
        fout << answ << '\n';
    }
    return 0;
}