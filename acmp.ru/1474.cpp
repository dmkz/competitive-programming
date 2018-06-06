#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    int a, b, h;
    std::cin >> a >> b >> h;
    std::cout << std::fixed << std::setprecision(6) 
        << 2 * b * std::sqrt(h*h+a*a/4.0) << ' ';
    std::cout << std::fixed << std::setprecision(6) 
        << std::sqrt(h*h+a*a/4.0) * b + std::sqrt(h*h+b*b/4.0) * a;
    return 0;
}