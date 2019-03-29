/*
    Задача: 300. Радар
    
    Решение: перебор, геометрия, дроби, O(n! * n)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define size(x) (int)(x).size()
typedef long long ll;

template<typename T> T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }

struct Frac {
    ll p, q;
    Frac(ll p_ = 0, ll q_ = 1) : p(p_), q(q_) {
        if (p == 0) { q = 1; }
        if (q < 0) { p = -p; q = -q; }
        assert(q != 0);
        ll g = gcd(std::abs(p), std::abs(q));
        p /= g; q /= g;
    }
    Frac operator*(const Frac& f) const { return Frac(p * f.p, q * f.q); }
    Frac operator+(const Frac& f) const { return Frac(p * f.q + f.p * q, q * f.q); }
    Frac operator-(const Frac& f) const { return Frac(p * f.q - f.p * q, q * f.q); }
    Frac operator/(const Frac& f) const { return Frac(p * f.q, q * f.p); }
};

bool operator<(const Frac& lhs, const Frac& rhs) {
    return (lhs - rhs).p < 0;
}

template<typename T> bool operator>(const T& lhs, const T& rhs) { return rhs < lhs; }
template<typename T> bool operator<=(const T& lhs, const T& rhs) { return !(lhs > rhs); }
template<typename T> bool operator>=(const T& lhs, const T& rhs) { return !(lhs < rhs); }
template<typename T> bool operator==(const T& lhs, const T& rhs) { return !(lhs < rhs || rhs < lhs); }
template<typename T> bool operator!=(const T& lhs, const T& rhs) { return !(lhs == rhs); }

struct Rocket {
    int t, v, s;
};

int getAngle(int curr, int next) {
    if (curr > next) { return getAngle(next, curr); }
    assert(curr <= next);
    return std::min(next - curr, 4 + curr - next);
}

int solve(const int tRot, const int dist, std::list<Rocket> rockets) {
    int answ = 1, side = rockets.begin()->s;
    Frac time = Frac(dist, rockets.begin()->v) + rockets.begin()->t;
    rockets.erase(rockets.begin());
    while (!rockets.empty()) {
        for (auto it = rockets.begin(); it != rockets.end(); it++) {
            if (Frac(dist, it->v) + it->t < time) {
                return answ-1;
            }
        }
        auto best = rockets.begin();
        if (Frac(time) + getAngle(side, best->s) * tRot > Frac(dist, best->v) + best->t) {
            break;
        }
        time = Frac(dist, best->v) + best->t;
        side = best->s;
        answ++;
        rockets.erase(best);
    }
    return answ;
}

int main() {
    std::vector<Rocket> arr(4);
    for (int i = 0; i < 4; ++i) {
        auto &it = arr[i];
        std::cin >> it.t >> it.v;
        it.s = i;
    }
    int tRot, dist, ret = 0;
    std::cin >> tRot >> dist;
    std::vector<int> perm = {0,1,2,3};
    do {
        std::list<Rocket> list;
        for (int i = 0; i < 4; ++i) {
            list.push_back(arr[perm[i]]);
        }
        ret = std::max(ret, solve(tRot, dist, list));
    } while (std::next_permutation(all(perm)));
    assert(ret > 0);
    if (ret == 4) { std::cout << "ALIVE\n"; }
    else { std::cout << ret << "\n"; }
    return 0;
}