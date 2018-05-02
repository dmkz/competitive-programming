/*
    Пусть есть два призрака со скоростями (vx1, vy1) и (vx2, vy2)
    Они напугают друг друга, когда их x координаты и y координаты совпадут
    x1 = x1_0 + vx1 * t
    y1 = y1_0 + vy2 * t
    
    x2 = x2_0 + vx2 * t
    y2 = y2_0 + vy2 * t
    
    x1_0 + vx1 * t = x2_0 + vx2 * t
    y1_0 + vy2 * t = y2_0 + vy2 * t
    
    vx1 * t - vx2 * t = x2_0 - x1_0
    vy1 * t - vy2 * t = y2_0 - y1_0 = a * x2_0 + b - a * x1_0 - b = a * (x2_0 - x1_0)
    
    a * (vx1 * t - vx2 * t) = vy1 * t - vy2 * t
    
    a * vx1 - vy1 = a * vx2 - vy2 - условие на то, есть ли пересечение
    
    Нужно вычесть количество сонаправленных векторов, так как они не пересекутся
*/

#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wunused-result"

typedef int64_t Int;
typedef std::pair<Int, Int> pair;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    
    std::map<pair, Int> nParallel;
    std::map<Int, Int> nEqual;
    
    Int n, a, b, answ = 0; 
    std::cin >> n >> a >> b;
    for (Int i = 0; i < n; ++i) {
        Int x, vx, vy;
        std::cin >> x >> vx >> vy;
        answ += nEqual[a * vx - vy] - nParallel[{vx, vy}];
        nEqual[a * vx - vy]++;
        nParallel[{vx, vy}]++;
    }
    std::cout << 2 * answ << std::endl;    
    return 0;
}