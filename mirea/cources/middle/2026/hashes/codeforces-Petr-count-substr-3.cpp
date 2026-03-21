#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

const ull mod = (1LL << 61) - 1;

const ull base = [](){
    size_t seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed);
    auto dist = uniform_int_distribution<ull>(mod / 2, mod - 20);
    ull result = dist(gen);
    if (result % 2 == 0)
        result++;
    return result;
}();

ull mul(ull a, ull b) {
    ull a0 = (uint32_t)a, b0 = (uint32_t)b;
    ull a1 = a >> 32, b1 = b >> 32;
    ull high = ((a1 * b1 << 3) & mod) + ((a1 * b1) >> 58);
    ull mid = ((a1 * b0 + b1 * a0) >> 29) + (((a1 * b0 + b1 * a0) << 32) & mod);
    ull ret = high + mid + ((a0 * b0) >> 61) + ((a0 * b0) & mod) + 1;
    ret = (ret >> 61) + (ret & mod);
    ret = (ret >> 61) + (ret & mod);
    return ret - 1;
}
ull add(ull a, ull b) {
    return (a += b) >= mod ? a -= mod : a;
}
ull sub(ull a, ull b) {
    return (a -= b) >= mod ? a += mod : a;
}

vector<ull> power = {1};

void precalc(int len) {
   while ((int)power.size() <= len)
       power.push_back(mul(power.back(), base));
}

auto buildPrefSums(const auto &s) {
    vector<ull> ps = {0};
    for (auto c : s)
        ps.push_back(add(mul(ps.back(), base), c));
    return ps;
}

auto getHash(const auto &ps, int L, int R) {
    L++, R++;
    return sub(ps[R], mul(ps[L-1], power[R-L+1]));
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
    auto ha = buildPrefSums(a).back();
    auto hb = buildPrefSums(b).back();
    
    vector<ull> Set;
    for (int len = std::max((int)a.size(), (int)b.size()); len <= (int)s.size(); len++) {
        for (int i = 0; i + len <= (int)s.size(); i++) {
            if (getHash(ps, i, i + (int)a.size() - 1) == ha &&
                getHash(ps, i + len - 1 - (int)b.size() + 1, i + len - 1) == hb)
            {
                Set.push_back(getHash(ps, i, i+len-1));
            }
        }
    }
    sort(Set.begin(), Set.end());
    cout << int(unique(Set.begin(), Set.end()) - Set.begin()) << endl;
}
