#include <bits/stdc++.h>
template<typename T> int sign(T t) { return t < 0 ? -1 : t > 0 ? +1 : 0; }

int getPart(int x, int y) {
// функция возвращает номер части плоскости, где оказалась точка
// это число от 0 до 7
// 0: луч y == 0, x < 0
// 1: четверть x < 0, y >= 0
// 2: луч x == 0, y >= 0
// 3: четверть x > 0, y >= 0
// 4: луч y == 0, x >= 0
// 5: четверть x > 0, y < 0
// 6: луч x == 0, y < 0
// 7: четверть x < 0, y < 0
    if (y == 0) { return x < 0 ? 0 : 4; }
    if (x == 0) { return y < 0 ? 6 : 2; }
    if (x < 0) { return y < 0 ? 7 : 1; }
    assert(x > 0);
    return y < 0 ? 5 : 3;
}

auto cross(int x1, int y1, int x2, int y2) {
// векторное произведение
    return 1LL * x1 * y2 - 1LL * y1 * x2;
}

int cmp(int x1, int y1, int x2, int y2) {
// функция сравнения в целых числах, использующая четверть плоскости
// и знак векторного произведения
    int id1 = getPart(x1,y1), id2 = getPart(x2,y2);
    if (id1 == id2) { return sign(cross(x2,y2,x1,y1)); }
    return sign(id2-id1);
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        printf("%d\n", cmp(x1,y1,x2,y2));
    }
    return 0;
}