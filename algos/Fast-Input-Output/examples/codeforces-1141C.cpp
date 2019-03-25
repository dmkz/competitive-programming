#include <bits/stdc++.h>
#include "FastIO.hpp"

int main() {
    FastIO::Reader fin;
    FastIO::Writer fout;
    typedef std::vector<int> vi;
    for (int n; fin >> n; ) {
        vi q(n-1);
        fin >> q;
        int v = 0, min = 0, max = 0;
        for (auto it : q) {
            v += it;
            min = std::min(min, v);
            max = std::max(max, v);
        }
        v = 1-min;
        vi p(n, v);
        for (int i = 1; i < n; ++i) {
            p[i] = p[i-1] + q[i-1];
        }
        vi tmp = p;
        #define all(x) (x).begin(), (x).end()
        std::sort(all(tmp));
        tmp.erase(std::unique(all(tmp)), tmp.end());
        if ((int)tmp.size() != n) {
            fout << -1 << '\n';
            continue;
        }
        bool ok = true;
        for (int i = 0; ok && i < n; ++i) {
            ok = ok && tmp[i] == i+1;
        }
        if (!ok) {
            fout << -1 << '\n';
        } else {
            for (auto it : p) {
                fout << it << ' ';
            }
            fout << '\n';
        }
    }
    return 0;
}