/*
    Задача: 117. Опасная зона
    
    Решение: геометрия, выпуклая оболочка, алгоритм джарвиса, O(n^2)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <set>
#include <cmath>

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
    // Чтение точек:
    int n; scanf("%d", &n);
    std::set<Point> pt;
    for (int i = 0; i < n; ++i) {
        int x, y; scanf("%d %d", &x, &y);
        pt.insert(Point{x,y});
    }
    // Точно войдет первая точка
    std::vector<Point> hull{*pt.begin()};
    pt.erase(pt.begin());
    
    // Кидаем остальные точки
    while (!pt.empty()) {
        if (hull.size() > 1u) { // Для проверки того, что выпуклая оболочка замкнулась
            pt.insert(hull[0]); // кидаем начальную точку выпуклой оболочки
        }
        // Ищем точку с максимальным углом:
        auto max = pt.begin();
        for (auto it = pt.begin(); it != pt.end(); it++) {
            if (less(hull.back(), *it, *max)) {
                max = it;
            }
        }
        // Добавляем в выпуклую оболочку:
        hull.push_back(*max);
        pt.erase(max);
        // Проверяем условия выхода из цикла:
        if (hull.front() == hull.back() || pt.empty()) {
            break;
        }
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
    printf("%d", (int)std::round(std::abs(square)/2.0));
    return 0;
}