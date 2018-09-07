/*
    Задача: 117. Опасная зона
    
    Решение: геометрия, выпуклая оболочка, алгоритм джарвиса, O(n^2)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <set>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>

struct Point {
    int x, y;
    
    int norm2() const {
        return x * x + y * y;
    }
};

bool operator<(const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator==(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

Point operator-(const Point& a, const Point& b) {
    return Point{a.x - b.x, a.y - b.y};
}

// Векторное произведение векторов a x b:
int cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

// Векторное произведение векторов: (from, to1) x (from, to2)
int cross(const Point& from, const Point& to1, const Point& to2) {
    return cross(to1-from, to2-from);
}

// Сравнение двух точек относительно третьей по углу:
bool less(const Point& from, const Point& to1, const Point& to2) {
    int sign = cross(from, to1, to2);
    return sign > 0 || (sign == 0 && (to1 - from).norm2() < (to2-from).norm2());
}

int main() {
    double time = (double)clock();
    std::vector<Point> pt;
    /* Генерация худшего теста:
    for (int i = 0; i < 5000; ++i) {
        pt.insert(pt.end(), Point{   0,    i});
        pt.insert(pt.end(), Point{5000,    i});
        pt.insert(pt.end(), Point{   i, 5000});
        pt.insert(pt.end(), Point{   i,    0});
    }
    */
    // Чтение точек:
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int x, y; scanf("%d %d", &x, &y);
        pt.insert(pt.end(), Point{x,y});
    }
    std::sort(pt.begin(), pt.end());
    pt.erase(std::unique(pt.begin(), pt.end()), pt.end());
    // Точно войдет первая точка
    std::vector<Point> hull{*pt.begin()};
    pt.erase(pt.begin());
    
    // Кидаем остальные точки
    while (!pt.empty()) {
        // Ищем точку с максимальным углом:
        auto max = pt.begin();
        for (auto it = pt.begin(); it != pt.end(); it++) {
            if (less(hull.back(), *it, *max)) {
                max = it;
            }
        }
        // Проверяем не выгоднее ли замкнуть оболочку вместо добавления новой точки:
        if (hull.size() > 1u && less(hull.back(), hull.front(), *max)) {
            break;
        }
        // Добавляем в выпуклую оболочку:
        hull.push_back(*max);
        pt.erase(max);
    }
    // Если по каким-то причинам выпуклая оболочка не замкнулась - замыкаем:
    if (!(hull.back() == hull.front())) {
        hull.push_back(hull.front());
    }
    // Считаем площадь фигуры:
    int square = 0;
    for (int i = 1; i < (int)hull.size(); ++i) {
        square += cross(hull[i-1], hull[i]);
    }
    printf("%d\n", (int)std::round(std::abs(square)/2.0));
    fprintf(stderr, "time = %0.3fs\n", ((double)clock() - time) / CLOCKS_PER_SEC);
    return 0;
}