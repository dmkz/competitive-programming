#include <bits/stdc++.h>
using namespace std;
const int base = 15032027;
const int mod = (int)1e9+7;

vector<int> power = {1};

void precalc(int len) {
   while ((int)power.size() <= len)
       power.push_back(int(power.back() * 1LL * base % mod));
}

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

int compare(const auto &s, const auto &ps, int pos1, int pos2, int len) {
// return {-1, 0, +1}
    int low = 0, high = len + 1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        auto h1 = getHash(ps, pos1, pos1 + mid - 1);
        auto h2 = getHash(ps, pos2, pos2 + mid - 1);
        if (h1 == h2) low = mid;
        else high = mid;
    }
    // здесь закончили
    // первые low символов совпадают
    if (high > len)
        return 0;
    if (s[pos1 + high - 1] < s[pos2 + high - 1])
        return -1;
    return +1;
}

main() {
    precalc(200200);
    string s;
    cin >> s;
    const int n = (int)s.size();
    s = s + s;
    
    auto ps = buildPrefSums(s);
    int minI = 0;
    for (int i = 1; i < n; i++)
        if (compare(s, ps, minI, i, n) > 0)
            minI = i;
    cout << s.substr(minI, n) << endl;
}
