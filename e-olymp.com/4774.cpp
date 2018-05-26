//
//    Построение выпуклой оболочки и вывод координат точек, входящих в нее, в порядке обхода против часовой стрелки
//    

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

typedef long double Real;
typedef long long Int;

struct Point {
    int x, y, id; // Координаты и порядковый номер точки
    
    Int norm2() const { // Квадрат нормы
        return Int(x)*x+Int(y)*y;
    }
    
    Point operator-(const Point& p) const { // Разность точек
        return Point{x-p.x, y-p.y, 0};
    }
};

// Векторное произведение вектора a на вектор b:
Int cross(const Point& a, const Point& b) {
    return Int(a.x) * b.y - Int(a.y) * b.x;
}

// Определение правого поворота:
bool right_rotate(const Point& a, const Point& b, const Point& c) {
    return cross(a-b, c-b) >= 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    
    // Чтение точек:
    int n; std::cin >> n;
    std::vector<Point> points;
    for (int i = 1; i <= n; ++i) {
        int x, y; 
        std::cin >> x >> y;
        points.push_back(Point{x, y, i});
    }
    // Нахождение самой левой точки:
    auto it = min_element(points.begin(), points.end(), [](const Point& a, const Point& b){
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    std::swap(*it, points[0]);
    
    // Сортировка точек по полярному углу относительно самой левой:
    const Point& first = points[0];
    std::sort(points.begin()+1, points.end(), [first](const Point& a, const Point& b) {
        auto vector_a = a - first;
        auto vector_b = b - first;
        auto angle1 = std::atan2((Real)vector_a.y, (Real)vector_a.x);
        auto angle2 = std::atan2((Real)vector_b.y, (Real)vector_b.x);
        return angle1 < angle2 || (angle1 == angle2 && vector_a.norm2() < vector_b.norm2());
    });
    points.push_back(points[0]); // дублирование самой левой точки для замкнутости
    
    // Построение выпуклой оболочки:
    std::vector<Point> convex_hull{points[0], points[1]};
    for (int i = 2; i <= n; ++i) {
        convex_hull.push_back(points[i]);
        for (int j = (int)convex_hull.size()-1; j >= 2; --j) {
            if (right_rotate(convex_hull[j-2], convex_hull[j-1], convex_hull[j])) {
                convex_hull[j-1] = convex_hull[j];
                convex_hull.pop_back();
            } else {
                break;
            }
        }
    }
    // Проверка на невырожденность:
    // assert(convex_hull.size() >= 4u); 
    
    // Проверка на замкнутость:
    assert(convex_hull.front().id == convex_hull.back().id);
    convex_hull.pop_back();
    
    // Вывод выпуклой оболочки:
    std::cout << (int)convex_hull.size() << std::endl;
    for (const auto& it : convex_hull) {
        std::cout << (int)it.x << ' ' << (int)it.y << '\n';
    }
    
    return 0;
}