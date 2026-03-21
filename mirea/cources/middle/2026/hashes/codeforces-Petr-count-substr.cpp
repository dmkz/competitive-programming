#include <bits/stdc++.h>
using namespace std;
const int base = 15032027;
const int mod = (int)1e6+3;

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
    precalc(2020);
    string s, a, b;
    cin >> s >> a >> b;
    auto ps = buildPrefSums(s);
    int ha = buildPrefSums(a).back();
    int hb = buildPrefSums(b).back();
    
    int answ{};
    for (int len = std::max<int>(a.size(), b.size()); len <= (int)s.size(); len++) {
        set<int> Set;
        for (int i = 0; i + len <= (int)s.size(); i++) {
            if (getHash(ps, i, i + (int)a.size() - 1) == ha &&
                getHash(ps, i + len - 1 - (int)b.size() + 1, i + len - 1) == hb)
            {
                Set.insert(getHash(ps, i, i+len-1));
            }
        }
        answ += (int)Set.size();
    }
    cout << answ << endl;
}
