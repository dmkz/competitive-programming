/*
    Задача: 267. Ксерокопии
    
    Решение: нод, перебор, математика, O(x+y)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
template<typename T>
T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}
uint32_t solve(uint32_t n, uint32_t x, uint32_t y) {
    auto g = x / gcd(x, y) * y;
    uint32_t cx = g / x;
    uint32_t cy = g / y;
    uint32_t k = n / (cx + cy);
    uint32_t ans = g * k;
    uint32_t delta = ~0;
    n -= k * (cx + cy);
    for (uint32_t nx = 0; nx <= n; ++nx) {
        delta = std::min(delta, std::max(nx * x, (n - nx) * y));
    }
    return ans + delta;
}
int main() {
    uint32_t n, x, y;
    std::cin >> n >> x >> y;
    std::cout << std::min(x,y) + solve(n-1,x,y) << std::endl;
    return 0;
}