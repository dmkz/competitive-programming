#include <bits/stdc++.h>

using namespace std;
using pii = pair<int,int>;
using vpii = vector<pii>;

const int NMAX = (int)1e7+7;
const auto minDiv = [](){
    // предподсчитываем минимальный делитель
    vector<int> minDiv(NMAX);
    for (int x = 2; x < NMAX; x++) {
        if (!minDiv[x]) {
            for (int y = x; y < NMAX; y+=x)
                if(!minDiv[y]) minDiv[y] = x;
        }
    }
    return minDiv;
}();

void factor(int x, vpii &divisors) {
// факторизация за логарифм. divisors = пары {p, k}
    divisors.clear();
    while (x > 1) {
        int p = minDiv[x];
        x /= p;
        if (divisors.empty() || divisors.back().first != p)
            divisors.push_back({p, 0});
        if (divisors.back().first == p)
            divisors.back().second++;
    }
}

int binpow(int p, int k) {
    return k == 0 ? 1 : p * binpow(p, k-1);
}

int geom(int p, int k) {
    return k == 0 ? 1 : 1 + p * geom(p, k-1);
}

int main() {
    int n; cin >> n;
    vpii divisors;
    int64_t a{}, b{}, c{}, d{};
    for (int x = 1; x <= n; x++) {
        factor(x, divisors);
        int phi = 1, s1 = 1, s0 = 1;
        for (const auto &[p,k] : divisors) {
            phi *= binpow(p, k-1)*(p-1);
            s1 *= geom(p, k);
            s0 *= k+1;
        }
        a += minDiv[x];
        b += s0;
        c += s1;
        d += phi;
    }
    std::cout << a << ' ' << b << ' ' << c << ' ' << d << std::endl;
}