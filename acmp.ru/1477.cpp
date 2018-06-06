#include <iostream>
#include <algorithm>

int solve(int w, int h) {
    // Прямые перпендикулярны - случай 4 квадратов:
    if (w == h && w % 2 == 0) {
        return 4;
    }
    
    // Прямые параллельны - случай 3 квадратов:
    if (h == 3LL * w || w == 3LL * h) {
        return 3;
    }
    
    // Прямые перпендикулярны - случай 2 квадратов:
    if ((w == h && w > 1) || (w % 2 == 0 && w / 2 <= h) || (h % 2 == 0 && h / 2 <= w)) {
        return 2;
    }
    
    // Прямые параллельны - случай 2 квадратов:
    if (h >= 2 * w || w >= 2 * h) {
        return 2;
    }
    
    // 1 квадрат можно получить всегда:
    return 1;
}

int main() {
    int w, h;
    std::cin >> w >> h;
    std::cout << solve(w, h);
    return 0;
}