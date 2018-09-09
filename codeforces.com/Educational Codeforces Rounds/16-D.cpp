/*
    Problem: 710D. Two Arithmetic Progressions
    
    Solution: math, gcd, extended euclid, O(log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>

typedef long long ll;

template<typename T>
T gcd(T a, T b, T & x, T & y) {
	assert(a || b);
    if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	T x1, y1;
	T d = gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

template <typename T>
bool find_any_solution(T a, T b, T c, T & x0, T & y0, T & g) {
	g = gcd(std::abs(a), std::abs(b), x0, y0);
	if (c % g != 0) return false;
	x0 *= c / g;
	y0 *= c / g;
	if (a < 0) x0 *= -1;
	if (b < 0) y0 *= -1;
	return true;
}

int main() {
    ll a1, b1, a2, b2, L, R; 
    std::cin >> a1 >> b1 >> a2 >> b2 >> L >> R;
    if (b1 > R || b2 > R) {
        std::cout << 0; return 0;
    }
    ll k0, t0, g;
    if (!find_any_solution(a1,-a2,b2-b1,k0,t0,g)) {
        std::cout << 0; return 0;
    }
    
    // x1 = a1 * k + b1
    // x2 = a2 * t + b2
    // a1 * k + b1 <= R
    // k <= (R - b1) / a1
    ll k_max = (R-b1) / a1;
    while (a1 * k_max+b1 > R) --k_max;
    while (a1 * (k_max+1)+b1 <= R) ++k_max;
    // k >= (L-b1)/a1
    ll k_min = (L-b1)/a1;
    while (a1 * k_min+b1 < L) ++k_min;
    while (a1 * (k_min-1)+b1 >= L) --k_min;
    // t <= (R-b2)/a2
    ll t_max = (R-b2) / a2;
    while (a2 * t_max+b2 > R) --t_max;
    while (a2 * (t_max+1)+b2 <= R) ++t_max;
    // t >= (L-b2)/a2
    ll t_min = (L-b2)/a2;
    while (a2 * t_min+b2 < L) ++t_min;
    while (a2 * (t_min-1)+b2 >= L) --t_min;
    k_min = std::max(ll(0), k_min);
    t_min = std::max(ll(0), t_min);
    // k = k0 + dk * n >= k_min <=> n >= (k_min - k0) / dk
    // t = t0 + dt * n >= t_min <=> n >= (t_min - t0) / dt
    ll dk = a2 / g, dt = a1 / g;
    ll n_min_k = (k_min - k0) / dk;
    ll n_min_t = (t_min - t0) / dt;
    while (k0 + dk * (n_min_k-1) >= k_min)--n_min_k;
    while (k0 + dk * n_min_k < k_min)++n_min_k;
    while (t0 + dt * (n_min_t-1) >= t_min)--n_min_t;
    while (t0 + dt *  n_min_t     < t_min)++n_min_t;
    // k = k0 + dk * n <= k_max <=> n <= (k_max - k0) / dk
    ll n_max_k = (k_max - k0) / dk;
    ll n_max_t = (t_max - t0) / dt;
    while (k0 + dk * (n_max_k+1) <= k_max)++n_max_k;
    while (k0 + dk *  n_max_k     > k_max)--n_max_k;
    while (t0 + dt * (n_max_t+1) <= t_max)++n_max_t;
    while (t0 + dt *  n_max_t     > t_max)--n_max_t;
    std::cout << std::max(ll(0), std::min(n_max_k, n_max_t) - std::max(n_min_k, n_min_t) + 1);
    return 0;
}