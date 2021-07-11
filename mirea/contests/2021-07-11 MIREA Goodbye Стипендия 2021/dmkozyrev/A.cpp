#include <bits/stdc++.h>
int main() {
    int x1,y1,x2,y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    // x1 <= точка <= y1
    // x2 <= точка <= y2
    // значит, что:
    // max(x1,x2) <= точка <= min(y1,y2)
    // это и будет отрезок пересечения
    // осталось проверить, что он положительной длины
    int x = std::max(x1,x2);
    int y = std::min(y1,y2);
    if (x >= y) std::cout << "-1" << std::endl;
    else std::cout << x << ' ' << y << std::endl;
    return 0;
}