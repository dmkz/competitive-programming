#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll mod = (1LL << 61) - 1;

const ll base = [](){
    size_t seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed);
    auto dist = uniform_int_distribution<ll>(mod / 2, mod - 20);
    ll result = dist(gen);
    if (result % 2 == 0)
        result++;
    return result;
}();

ll mul(ll a, ll b) {
    return ll(__int128(a) * b % mod);
}

ll add(ll a, ll b) {
    return ll((__int128(a) + b) % mod);
}

ll sub(ll a, ll b) {
    return ll(((__int128(a) - b) % mod + mod) % mod);
}

vector<ll> power = {1};

void precalc(int len) {
   while ((int)power.size() <= len)
       power.push_back(mul(power.back(), base));
}

auto buildPrefSums(const auto &s) {
    vector<ll> ps = {0};
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
    
    vector<ll> Set;
    for (int len = std::max<int>(a.size(), b.size()); len <= (int)s.size(); len++) {
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
