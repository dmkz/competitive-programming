#include <bits/stdc++.h>
using namespace std;
const int base = 15032027;
const int mod = (int)1e9+7;

const auto power = []()
                   {
                       vector<int> result = {1};
                       while ((int)result.size() <= 50000)
                           result.push_back(int(result.back() * 1LL * base % mod));
                       return result;
                   }();

auto buildPrefSums(const auto &s) {
    vector<int> ps = {0};
    for (auto c : s)
        ps.push_back(int((ps.back() * 1LL * base + c) % mod));
    return ps;
}

auto getHash(const auto &ps, int L, int R) {
    L++, R++;
    return ((ps[R] - ps[L-1] * 1LL * power[R-L+1]) % mod + mod) % mod;
}

main() {
    string s, t;
    cin >> s;
    cin >> t;
    auto ps = buildPrefSums(s);
    auto pt = buildPrefSums(t);
    for (int i = 0; i + (int)t.size() <= (int)s.size(); i++)
        if (getHash(ps, i, i + (int)t.size() - 1) == getHash(pt, 0, (int)t.size() - 1))
            cout << i << ' ';
}
