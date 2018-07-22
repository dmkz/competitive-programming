/*
    Задача: Треугольники - 3
    
    Решение: сортировка, бинарный поиск, геометрия, отрезки, O(n^2 log(n))
    
    Автор: Дмитрий Козырев, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <algorithm>
#include <vector>

typedef long long ll;

struct Seg {

    int x, y, dx, dy;
    
    ll norm2;
    
    Seg(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0) : x(x1), y(y1), dx(x2-x1), dy(y2-y1) { 
        norm2 = ll(dx)*(dx)+ll(dy)*(dy);
    }
    
    inline Seg inv() const {
        Seg ret = *this;
        ret.dx = -ret.dx;
        ret.dy = -ret.dy;
        return ret;
    }
};

inline bool operator<(const Seg& a, const Seg& b) {
    if (a.norm2 < b.norm2) return true;
    if (a.norm2 > b.norm2) return false;
    return a.x < b.x || (a.x == b.x && (a.y < b.y || (a.y == b.y && (a.dx < b.dx || (a.dx == b.dx && a.dy < b.dy)))));
}

int main() {
    int n; scanf("%d", &n);
    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &x[i], &y[i]);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        // Проводим отрезки из i-й точки до всех остальных и сортируем их:
        std::vector<Seg> segs;
        segs.reserve(n);
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            segs.push_back(Seg(x[i],y[i],x[j],y[j]));
        }
        std::sort(segs.begin(), segs.end());
        // Для каждого отрезка ищем количество вариантов комбинирования с другими отрезками
        // Не забываем вычесть количество вариантов получения вырожденных треугольников
        for (int j = 0; j < (int)segs.size(); ++j) {
            auto pair = std::equal_range(segs.begin()+j+1, segs.end(), segs[j], [](const Seg& a, const Seg& b) {
                return a.norm2 < b.norm2;
            });
            ans += int(pair.second - pair.first) - (int)std::binary_search(segs.begin()+j+1, segs.end(), segs[j].inv());
        }
    }
    printf("%d", ans);
    return 0;
}