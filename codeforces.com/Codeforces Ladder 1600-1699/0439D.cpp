/*
    Problem: 439D. Devu and his Brother
    
    Solution: sorting, greedy, binary search, prefix sums, O((n+m)*(log(n)+log(m)))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<ll> vl;

const ll INF = (ll)1e18L;

struct PrefSum {
    vl data;
    PrefSum(const vi& arr) {
        data.push_back(0);
        for (auto& it : arr) {
            data.push_back(data.back()+it);
        }
    }
    ll operator()(int pos, int len) const {
        return data[pos+len] - data[pos];
    }
};

ll solve(vi a, vi b) {
    std::sort(all(a));
    std::sort(all(b));
    PrefSum sa(a), sb(b);
    ll answ = INF;
    for (int i = 0, m = (int)b.size(); i < m; ++i) {
        ll item = b[i];
        int len = int(std::lower_bound(all(a), item) - a.begin());
        ll tmp = item * len - sa(0, len) + sb(i, m - i) - item * (m - i);
        answ = std::min(answ, tmp);
    }
    for (int i = 0, n = (int)a.size(); i < n; ++i) {
        ll item = a[i];
        int len = int(b.end()-std::lower_bound(all(b), item));
        int pos = (int)b.size()-len;
        ll tmp = item * (i+1) - sa(0, i+1) + sb(pos, len) - item * len;
        answ = std::min(answ, tmp);
    }
    return answ;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n, m;
    while (std::cin >> n >> m) {
        std::vector<int> a(n), b(m);
        for (auto& it : a) { std::cin >> it; }
        for (auto& it : b) { std::cin >> it; }
        std::cout << solve(a, b) << std::endl;
    }
    return 0;
}