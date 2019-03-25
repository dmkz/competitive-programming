#include <bits/stdc++.h>
#include "FastIO.hpp"

int main() {
    FastIO::Reader fin;
    FastIO::Writer fout;
    typedef std::vector<int> vi;
    typedef long long ll;
    ll h; int n;
    while (fin >> h >> n) {
        vi d(n);
        fin >> d;
        ll sum = 0, min = 0, answ = 0;
        for (auto &it : d) { sum += it; min = std::min(min, sum); }
        if (sum >= 0) {
            if (h + min <= 0) {
                while (h > 0) {
                    h += d[answ];
                    answ++;
                }
                assert(h <= 0);
            } else {
                answ = -1;
            }
        } else {
            if (h + min <= 0) {
                while (h > 0) {
                    h += d[answ];
                    answ++;
                }
                assert(h <= 0);
            } else {
                ll low = 0, high = h / (-sum) + 1;
                while (high - low > 1) {
                    ll mid = (low + high) / 2;
                    if (h + mid * sum + min <= 0) {
                        high = mid;
                    } else {
                        low = mid;
                    }
                }
                answ += high * (ll)d.size();
                h += high * sum;
                int p = 0;
                while (h > 0 && p < (int)d.size()) {
                    h += d[p];
                    p++;
                }
                assert(h <= 0);
                answ += p;
            }
        }
        fout << answ << '\n';
    }
    return 0;
}