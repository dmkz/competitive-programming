// need to compile with C++20
#include <bits/stdc++.h>
using ll = long long;
// v1 = 6
// v2 = 1/10
// v3 = 1/120
struct Frac {
    
    ll p{0}, q{1};
    
    Frac(ll p_ = 0, ll q_ = 1)
        : p(p_), q(q_)
    { normalize(); }
    
    void normalize() {
        auto g = std::gcd(std::abs(p),std::abs(q));
        p /= g, q /= g;
        if(p==0)q=1;
        if(q<0)p*=-1,q*=-1;
    }
    
    std::strong_ordering operator<=>(const Frac &f) const {
        return (*this - f).p <=> 0;
    }
    
    Frac operator-(const Frac &b) const {
        return Frac(p * b.q - b.p * q, q * b.q);
    }

    Frac operator+(const Frac &b) const {
        return Frac(p * b.q + b.p * q, q * b.q);
    }

    Frac operator*(const Frac &b) const {
        return Frac(p * b.p, q * b.q);
    }

    Frac operator/(const Frac &b) const {
        return Frac(p * b.q, q * b.p);
    }
};

auto solve(Frac v1, Frac v2, ll p, ll q) {
    std::vector<Frac> res;
    for (int i = 0; i < 60*60*12; i++) {
        auto p1 = Frac(360 * i)/(v1-v2) - Frac(p) / (Frac(q)*(v1-v2));
        auto p2 = Frac(360 * i)/(v1-v2) + Frac(p) / (Frac(q)*(v1-v2));
        for (auto p : {p1,p2})
            if (Frac(0) <= p && p <= Frac(12*60*60))
                res.push_back(p);
    }
    return res;
}
int main() {
    int p, q; std::cin >> p >> q;
    int x, y; std::cin >> x >> y;
    Frac v[4] = {0, Frac(360,60), Frac(360,60*60), Frac(360,12*60*60)};
    auto res = solve(v[x],v[y],p,q);
    std::cout << res.size() << '\n';
    for (auto [p,q] : res)
        std::cout << p << ' ' << q << '\n';
    return 0;
}
