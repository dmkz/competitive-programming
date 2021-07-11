#include <bits/stdc++.h>
using ld = long double;
int main() {
    std::cout << std::setprecision(24);
    ld x1,y1,x2,y2; std::cin >> x1 >> y1 >> x2 >> y2;
    // прямоугольные треугольники подобны
    // коэффициент подобия:
    ld k = y2 / y1;
    // зная коэффициент подобия, можно найти x-координату общей вершины
    // из равенства отношения катетов:
    // (x2-x)/(x-x1) = y2/y1 = k
    std::cout << (k*x1+x2)/(k+1) << std::endl;
    return 0;
}