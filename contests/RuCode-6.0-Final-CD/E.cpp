#pragma GCC optimize("Ofast,fast-math,unroll-loops")
#pragma GCC target("avx")
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
// 1. повернуть на exp(-i*a/180*pi)
// 2. поделить все иксы на p
// 3. искать окружность минимального радиуса, покрывающего всё
// 4. вывести радиус этой окружности
using Real = double;
const Real pi = std::acos(-1.0L);
const Real XMAX = 1e9L;
using Complex = std::complex<Real>;

void readAndTransform(std::vector<Real> &x, std::vector<Real> &y) {
    // чтение
    int n; std::cin >> n;
    x.resize(n);
    y.resize(n);
    for (int i = 0; i < n; i++) {
        int xx, yy; std::cin >> xx >> yy;
        x[i] = xx, y[i] = yy;
    }
    // поворот (в комплексных) + сжатие по Ох:
    int a, p; std::cin >> a >> p;
    for (int i = 0; i < n; i++) {
        auto P = Complex(x[i], y[i]) * std::polar<Real>(1, - a * pi / 180);
        x[i] = P.real() / p, y[i] = P.imag();
    }
}

const int MAX_ITERS = 100;

Real fxy(const double cx, const double cy,
         const double * __restrict x,
         const double * __restrict y,
         const int n)
{
    Real res = 0;
    for (int i = 0; i < n; i++) {
        const double dx = x[i] - cx;
        const double dy = y[i] - cy;
        const double r2 = dx * dx + dy * dy;
        res = (res < r2 ? r2 : res);
    }
    return res;
}

Real fx(const double cx, const std::vector<Real> &x, const std::vector<Real> &y)
{
    Real yLo = -XMAX, yHi = XMAX;
    for (int iters = MAX_ITERS; iters--; )
    {
        Real y1 = (2 * yLo + yHi) / 3;
        Real y2 = (yLo + 2 * yHi) / 3;
        if (fxy(cx,y1,&x[0],&y[0],isz(x)) < fxy(cx,y2,&x[0],&y[0],isz(x)))
            yHi = y2;
        else
            yLo = y1;
    }
    return fxy(cx,(yLo+yHi)/2,&x[0],&y[0],isz(x));
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout << std::fixed << std::setprecision(12);
    // читаем + поворачиваем + сжимаем:
    std::vector<Real> x, y;
    readAndTransform(x, y);
    // решаем задачу (нацонец-то)
    Real xLo = -XMAX, xHi = XMAX;
    for (int iters = MAX_ITERS; iters--; ) {
        Real x1 = (2 * xLo + xHi) / 3;
        Real x2 = (xLo + 2 * xHi) / 3;
        if (fx(x1,x,y) < fx(x2,x,y)) xHi = x2; 
        else xLo = x1;
    }
    std::cout << std::sqrt(fx((xLo+xHi)/2,x,y)) << std::endl;
}