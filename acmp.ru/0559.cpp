#include <bits/stdc++.h>

typedef long double Real;

const Real PI = std::acos(-1.0L);
const Real EPS = 1e-14;

// Square of figure from 0 to x:
Real square_till(Real r, Real d, Real x) {
    if (x <= r) {
        Real alpha = std::acos((r-x)/r);
        return r * r * (alpha - std::sin(2 * alpha) / 2);
    }
    if (x >= r + d) {
        return PI * r * r + d * 2 * r - square_till(r, d, 2 * r + d - x);
    }
    return PI * r * r / 2 + (x - r) * 2 * r;
}

// Square of figure from x to y:
Real square_before(Real r, Real d, Real x, Real y) {
    return square_till(r, d, y) - square_till(r, d, x);
}

// Find root of equation x = s / r^2 + sin(2*x) / 2 using binsearch:
Real solve_binsearch(Real s, Real r) {
    Real low = -100, high = 100;    
    while (high - low > EPS) {
        Real mid = (low + high) / 2;
        Real value = mid - s / r / r - std::sin(2 * mid) / 2;
        if (value >= 0) {
            high = mid;
        } else {
            low = mid;
        }
    }
    return (low + high) / 2;
}

// Find root of equation x = s / r^2 + sin(2*x) / 2 using newton iterations
Real solve_newton(Real s, Real r) {
    // next = curr - f(curr) / f'(curr)
    // f(x) = x - s / r^2 - sin(2*x) / 2
    // f'(x) = 1 - cos(2*x)
    Real curr = s / r / r + 0.5; // x0
    while (true) {
        Real next = curr - (curr - s / r / r - std::sin(2*curr) / 2) / (1 - std::cos(2*curr));
        if (std::abs(next - curr) < EPS) {
            break;
        }
        curr = next;
    }
    return curr;
}

Real solve_equation(Real s, Real r) {
    return solve_newton(s, r); // or solve_binsearch(s, r);
}

// Get next from x = x1 point x2: square between x1 and x2 = s
Real next(Real d, Real r, Real s, Real x1) {
    if (square_before(r, d, x1, r) + EPS >= s) {
        Real angle = solve_equation(square_till(r, d, x1) + s, r);
        return r - std::cos(angle) * r;
    }
    if (square_before(r, d, x1, r + d) + EPS >= s) {
        if (x1 <= r) {
            return (s - PI * r * r / 2 + square_till(r, d, x1)) / (2 * r) + r;
        } else {
            return s / (2 * r) + x1;
        }
    }
    if (square_before(r, d, x1, 2 * r + d) + EPS >= s) {
        Real angle = solve_equation(PI * r * r / 2 - (s + square_before(r, d, r+d, x1)), r);
        return r + d + r * std::cos(angle);
    }
    return -1;
}

int main() {
    Real d, r, n, x = 0; 
    std::cin >> d >> r >> n;
    auto s = square_till(r, d, 2 * r + d) / n;
    for (int i = 1; i < n; ++i) {
        x = ::next(d, r, s, x);
        assert(x != -1);
        std::cout << std::fixed << std::setprecision(6) << x << "\n";
    }
    return 0;
}