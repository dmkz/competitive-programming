/*
    Задача: 856. Космический кегельбан
    
    Решение: геометрия, прямая, точка, окружность, бинарный поиск, O(n log(n))
    
    Автор: Дмитрий Козырев, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <functional>

typedef long double Real;

const Real PI = std::acos(Real(-1));

struct Point {
    Real x, y;
    
    static Point read() {
        Real x_, y_;
        std::cin >> x_ >> y_;
        return Point{x_, y_};
    }
    
    inline Real norm() const {
        return std::sqrt(x * x + y * y);
    }
    
    inline Point operator-(const Point& other) const {
        return Point{x-other.x, y-other.y};
    }
    
    inline Point operator+(const Point& other) const {
        return Point{x+other.x, y+other.y};
    }
    
    inline Point operator/(const Real q) const {
        return Point{x / q, y / q};
    }
    
    inline Point operator*(const Real q) const {
        return Point{x * q, y * q};
    }
    
    inline Point rotate(const Real angle) const {
        return Point {
            std::cos(angle) * x - std::sin(angle) * y,
            std::sin(angle) * x + std::cos(angle) * y
        };
    }
};

inline Real det(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

struct Line {

    Real A, B, C;

    Line(const Point& a, const Point& b) {
        // -(b.y-a.y)*(x-a.x) + (b.x-a.x)*(y - a.y) = 0
        A = a.y - b.y;
        B = b.x - a.x;
        C = -(a.x * A + a.y * B);
    }
    
    inline Point intersect(const Line& L) const {
        auto q = det(Point{ A, B}, Point{ L.A, L.B});
        auto a = det(Point{-C, B}, Point{-L.C, L.B});
        auto b = det(Point{ A,-C}, Point{ L.A,-L.C});
        return Point{a / q, b / q};
    }
    
    inline Real value(const Point& p) const {
        return A * p.x + B * p.y + C;
    }
};

inline Real dist(const Point& p, const Line& L) {
    return std::abs(L.value(p)) / Point{L.A, L.B}.norm();
}

inline Real dist(const Point& a, const Point& b) {
    return (a-b).norm();
}

int solve(int n, Real r, Real R, Point C, Point V) {
    // Cтроим две прямые, отвечающие за пересечения кегель с шаром:
    Line L1(C+V.rotate(PI/2)*R, C+V.rotate(PI/2)*R+V);
    Line L2(C-V.rotate(PI/2)*R, C-V.rotate(PI/2)*R+V);
    // Тестовая точка, которая точно лежит справа от каждой прямой:
    Point test = C + V.rotate(-PI/2) * 2 * R;
    // Максимальный и минимальный номера кегель в ряду:
    int max_id = (n % 2 == 1) ? ( n / 2) : (( n-1) / 2);
    int min_id = (n % 2 == 1) ? (-n / 2) : ((-n-1) / 2);
    // Центр кегли в ряду по ее номеру:
    std::function<Point(int)> point = [n](const int id) {
        if (n % 2 == 1) {
            return Point{Real(id) * 2000, Real(n-1) * 1000};
        } else {
            return Point{1000 + Real(id) * 2000, Real(n-1) * 1000};
        }
    };
    // Бинарный поиск по первой кегле слева от левой прямой, не пересекающей ее:
    int low = min_id - 1, high = max_id + 1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (L1.value(point(mid)) * L1.value(test) <= 0) {
            low = mid;
        } else {
            high = mid;
        }
    }
    while (low >= min_id && dist(point(low), L1) <= r) --low;
    // Количество целых кегель слева:
    int left = std::max(0, low - min_id + 1);
    // Бинарный поиск по первой кегле справа от правой прямой, не пересекающей ее:
    low = min_id - 1, high = max_id + 1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (L2.value(point(mid)) * L2.value(test) <= 0) {
            low = mid;
        } else {
            high = mid;
        }
    }
    low = high;
    while (low <= max_id && dist(point(low), L2) <= r) ++low;
    // Количество целых кегель справа:
    int right = std::max(0, max_id - low + 1);
    return n - left - right;
}

int main() {
    int r, n, R;
    std::cin >> r >> n >> R;
    
    Point P = Point::read();
    Point V = Point::read();
    P = P * 1000;
    V = V / V.norm();
    
    long long answ = 0;    
    for (int i = 1; i <= n; ++i) {
        answ += solve(i, r, R, P, V);
    }
    std::cout << answ;
    return 0;
}