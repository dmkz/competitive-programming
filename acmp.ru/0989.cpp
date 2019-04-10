/*
    Задача: 989. Окопы
    
    Решение: геометрия, отрезки, уравнение прямой, дроби, O(q)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>

typedef long long ll;

template<typename T> T gcd(T a, T b) { return b == T(0) ? a : gcd(b, a % b); }
template<typename T> T gcd(T a, T b, T c) { return gcd(a,gcd(b,c)); }
template<typename T> T lcm(T a, T b) { return a / gcd(a,b) * b; }
template<typename T> T lcm(T a, T b, T c) { return a / gcd(a,b,c) * b * c; }

struct Frac {
    ll p, q;
    Frac(ll p_ = 0, ll q_ = 1) : p(p_), q(q_) { norm(); }
    void norm() {
        auto g = gcd(std::abs(p), std::abs(q));
        p /= g; q /= g;
        if (q < 0) { p = -p; q = -q; }
        if (p == 0) { q = 1; }
    }
    Frac operator-() const { return Frac(-p,q); }
    Frac operator+(const Frac& f) const { return Frac(p * f.q + f.p * q, f.q * q); }
    Frac operator-(const Frac& f) const { return *this + (-f); }
    Frac operator*(const Frac& f) const { return Frac(p * f.p, q * f.q); }
    Frac operator/(const Frac& f) const { return Frac(p * f.q, q * f.p); }
};

bool operator<(const Frac& a, const Frac& b) { return (a - b).p < 0; }

template<typename T> bool operator>(const T& a, const T& b) { return b < a; }
template<typename T> bool operator>=(const T& a, const T& b) { return !(a < b); }
template<typename T> bool operator<=(const T& a, const T& b) { return !(a > b); }
template<typename T> bool operator!=(const T& a, const T& b) { return a < b || b < a; }
template<typename T> bool operator==(const T& a, const T& b) { return !(a != b); }

std::ostream& operator<<(std::ostream& os, const Frac &f) { return (f.q == 1 || f.p == 0) ? (os << f.p) : (os << f.p << "/" << f.q); }

struct Point {
    Frac x, y;
    Point(Frac x_ = Frac(), Frac y_ = Frac()) : x(x_), y(y_) { }
    Point ort() const { return Point(-y, x); }
    Point operator-() const { return Point(-x,-y); }
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return *this + (-p); }
    Point operator*(const Frac& f) const { return Point(x * f, y * f); }
    Point operator/(const Frac& f) const { return Point(x / f, y / f); }
};

std::ostream& operator<<(std::ostream& os, const Point &p) { return os << "{" <<  p.x << ", " << p.y << "}"; }

bool operator<(const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
Frac dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

Frac cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

void normalize(Frac& A, Frac& B, Frac& C) {
    auto l = lcm(A.q, B.q, C.q);
    A = A * l;
    B = B * l;
    C = C * l;
    auto g = gcd(std::abs(A.p), std::abs(B.p), std::abs(C.p));
    A = A / g;
    B = B / g;
    C = C / g;
    if (A < Frac(0)) { A = -A; B = -B; C = -C; }
    if (A == Frac(0) && B < Frac(0)) { B = -B; C = -C; }
}

void getABC(Point p, Point q, Frac& A, Frac& B, Frac& C) {
    // dot(point - p, ort(q - p)) == 0
    // dot(point, ord(q-p)) - dot(p, ort(q-p)) == 0
    auto vec = (q - p).ort();
    A = vec.x;
    B = vec.y;
    C = -dot(p,vec);
    normalize(A,B,C);
}

auto solve(Point a, Point b, Point c, Point d) {
    // Check if segments is a parts of one line
    Point p, q;
    if (cross(c-a,b-a) == Frac(0) && cross(d-c,b-a) == Frac(0)) {
        Point t = a, k = c;
        for (auto i : {a,b}) {
            for (auto j : {c,d}) {
                if (dot((j-i),(j-i)) < dot(k-t,k-t)) {
                    t = i;
                    k = j;
                }
            }
        }
        p = (t + k) / 2;
        q = p + (k-t).ort();
    } else if (cross(c-a, b-a) * cross(d-a, b-a) > Frac(0)) {
        p = a + (c - a) / 2;
        q = b + (c - a) / 2;
    } else {
        p = (a + c) / 2;
        q = (b + d) / 2;
    }
    Frac A, B, C;
    getABC(p,q,A,B,C);
    return std::make_tuple(A,B,C);
}

template<typename T>
int sign(T val) {
    return val > T(0) ? +1 : val < T(0) ? -1 : 0;
}

template<typename T>
auto sign(T A, T B, T C, Point p) {
    return sign(p.x * A + p.y * B + C);
}

bool check(Frac A, Frac B, Frac C, Point a, Point b, Point c, Point d) {
    int sa = sign(A,B,C,a);
    int sb = sign(A,B,C,b);
    int sc = sign(A,B,C,c);
    int sd = sign(A,B,C,d);
    return !(sa * sb == 1 && sd * sc == 1 && sa * sc == -1);
}

auto brute(Point a, Point b, Point c, Point d) {
    for (auto i : {a,b}) {
        for (auto j : {c,d}) {
            Frac A, B, C;
            std::tie(A,B,C) = solve(i,a+b-i,j,c+d-j);
            if (!check(A,B,C,a,b,c,d)) { return std::make_tuple(A,B,C); }
            std::tie(A,B,C) = solve(j,c+d-j,i,a+b-i);
            if (!check(A,B,C,a,b,c,d)) { return std::make_tuple(A,B,C); }
        }
    }
    assert(false);
}

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    int ax, ay, bx, by, cx, cy, dx, dy;
    while (std::cin >> ax >> ay >> bx >> by >> cx >> cy >> dx >> dy) {
        Point a(ax,ay), b(bx,by), c(cx,cy), d(dx,dy);
        if (a == b && a == c && a == d) { break; }
        Frac A, B, C;
        std::tie(A,B,C) = brute(a,b,c,d);
        std::cout << A << ' ' << B << ' ' << C << std::endl;
    }
    return 0;
}