#include <iostream>
#include <iomanip>
#include <cassert>

typedef long double Real;

inline Real f(Real x, int a, int b, int c, int d) {
    return d + x * (c + x * (b + x * a));
}

inline int sign(Real value) {
    return value >= 0 ? 1 : -1;
}

Real solve(int a, int b, int c, int d) {
// Корень уравнения находится бинпоиском
    Real high = 1e6;
    Real low = -1e6;
    int s_high = sign(f(high, a, b, c, d));
    int s_low = sign(f(low, a, b, c, d));
    assert(s_high != s_low);
    const Real eps = 1e-3;
    while (high - low > eps) {
        auto mid = (low + high) / 2;
        int s_mid = sign(f(mid, a, b, c, d));
        if (s_mid == s_high) {
            high = mid;
        } else {
            assert(s_mid == s_low);
            low = mid;
        }
    }
    return (low + high) / 2;
}

int main() {
    int a, b, c, d; 
    std::cin >> a >> b >> c >> d;
    std::cout << std::fixed << std::setprecision(3) << solve(a, b, c, d) << std::endl;  
    return 0;
}