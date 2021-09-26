#include <bits/stdc++.h>

// Структура для операций с точками и векторами:

typedef long double Real;

struct Point {
    Real x, y;
    
    Point(Real x_ = 0, Real y_ = 0) : x(x_), y(y_) { }
};
// сумма точек
Point operator+(Point a, Point b) {
    return Point(a.x + b.x, a.y + b.y);
}
// разность точек
Point operator-(const Point& a, const Point& b) {
    return Point(a.x - b.x, a.y - b.y);
}
// векторное произведение
Real cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}
// скалярное произведение
Real dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

// структура для прямой

struct Line {
    Real a, b, c;

    Line(Point A, Point B) {
        // уравнение прямой ax+by=c по двум точкам
        auto [xa,ya] = A;
        auto [xb,yb] = B;
        //(x-xa)/(xb-xa)=(y-ya)/(yb-ya);
        //(x-xa)(yb-ya)=(y-ya)*(xb-xa)
        //(x-xa)(yb-ya)-(y-ya)*(xb-xa)=0
        //(yb-ya)*x-xa*(yb-ya)-y*(xb-xa)+ya*(xb-xa)=0
        a = (yb-ya);
        b = (xa-xb);
        c = xa*(yb-ya)-ya*(xb-xa);
    }
    
    Point intersect(const Line& other) const {
        // пересечение двух прямых методом Крамера - решение СЛАУ 2 х 2
        auto a1 = other.a, b1 = other.b, c1 = other.c;
        // a * x + b * y = c
        // a1 * x + b1 * y1 = c1
        auto x = cross(Point(c,c1),Point(b,b1))/cross(Point(a,a1),Point(b,b1));
        auto y = cross(Point(a,a1),Point(c,c1))/cross(Point(a,a1),Point(b,b1));
        return Point(x,y);
    }
};

// функция для вывода ответа
void answer(Real x, Real y) {
    std::cout << "! " << (int)std::round(x) << ' ' << (int)std::round(y) << std::endl;
    std::exit(0);
}

Point ask(Point p) {
    std::cout << "? " << (int)p.x << ' ' << (int)p.y << std::endl;
    Point res;
    std::cin >> res.x >> res.y;
    if (dot(res,res) < 1E-9) {
        // нашли ответ - выводим
        answer(p.x, p.y);
    }
    return res;
}

int32_t main() {
    // Давайте спросим для одной случайной точки и для другой случайной точки
    // Тогда мы знаем две разные прямые, на которых лежит точка-ответ
    // осталось только найти точку пересечения двух прямых и вывести ответ
    // задача решается за 2 запроса
    
    // генератор псевдо-случайных чисел:
    std::mt19937 gen;
    auto random = [&](int a, int b) {
        return std::uniform_int_distribution<int>(a,b)(gen);
    };
    // генератор случайно точки из отрезка:
    const int MIN = -(int)1e9, MAX = (int)1e9;
    auto genCoord = [&]() {
        return random(MIN,MAX);
    };
    // генерируем две случайные точки:
    Point A(genCoord(),genCoord());
    Point C(genCoord(),genCoord());
    // делаем два запроса и строим две прямые:
    Line L1(A,A + ask(A));
    Line L2(C,C + ask(C));
    // пересекаем прямые
    auto p = L1.intersect(L2);
    // выводим ответ
    answer(p.x, p.y);
}