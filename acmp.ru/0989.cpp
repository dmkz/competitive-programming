/*
    Задача: 989. Окопы
    
    Решение: продвинутая геометрия, точка, дробь, прямая, O(q)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>

typedef long long ll;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll gcd(ll a, ll b, ll c) { return gcd(a,gcd(b,c)); }
ll lcm(ll a, ll b) { return a / gcd(a,b) * b; }
ll lcm(ll a, ll b, ll c) { return a / gcd(a,b,c) * b * c; }

struct Frac {
    ll p, q;
    Frac(ll p_ = 0, ll q_ = 1) : p(p_), q(q_) { normalize(); }
    Frac& normalize() { 
        if (q < 0) { p = -p; q = -q; } 
        if (p == 0) { q = 1; }
        auto g = gcd(std::abs(p), std::abs(q)); p /= g; q /= g;
        return *this;
    }
    Frac operator-() const { return Frac(-p,q); }
    Frac operator+(const Frac& f) const { return Frac(p * f.q + q * f.p, q * f.q); }
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

struct Point {
    Frac x, y;
    Point(Frac x_ = Frac(), Frac y_ = Frac()) : x(x_), y(y_) { }
    Point operator-() const { return Point(-x,-y); }
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return *this + (-p); }
    Point operator*(const Frac& val) const { return Point(x * val, y * val); }
    Point operator/(const Frac& val) const { return Point(x / val, y / val); }
    Point ort() const { return Point(-y,x); }
};

bool operator<(const Point& a, const Point& b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }

Frac dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }
Frac cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }

struct Line {
    Frac A, B, C;
    Line(Point a, Point b) {
        // dot((x - a), (b-a).ort()) == 0
        auto norm = (b-a).ort();
        A = norm.x; B = norm.y; C = dot(-a, norm);
        auto l = lcm(A.q, B.q, C.q);
        A = A * l; B = B * l; C = C * l;
        auto g = gcd(std::abs(A.p),std::abs(B.p),std::abs(C.p));
        A = A / g; B = B / g; C = C / g;
        if (A < Frac(0)) { A = -A; B = -B; C = -C; }
        if (A == Frac(0) && B < Frac(0)) { B = -B; C = -C; }
        assert(A != Frac(0) || B != Frac(0));
    }
    int sign(Point p) const {
        auto val = A * p.x + B * p.y + C;
        return val > Frac(0) ? +1 : val < Frac(0) ? -1 : 0;
    }
};

auto solve(Point a, Point b, Point c, Point d) {
    Point p, q;
    if (cross(b-a, d-c) == Frac(0) && cross(c-a,b-a) == Frac(0)) {
        Point t = a, k = c;
        for (auto i : {a,b}) {
            for (auto j : {c,d}) {
                if (dot(i-j,i-j) < dot(t-k,t-k)) {
                    t = i; k = j;
                }
            }
        }
        p = (t + k) / 2;
        q = p + (k-t).ort();
    } else {
        p = a + (c-a) / 2;
        q = b + (c-a) / 2;
    }
    return Line(p,q);
}

bool check(Line L, Point a, Point b, Point c, Point d) {
    return (L.sign(a) * L.sign(b) == 1 && L.sign(c) * L.sign(d) == 1 && L.sign(a) * L.sign(c) == -1);
}

auto brute(Point a, Point b, Point c, Point d) {
    for (auto i : {a,b}) {
        for (auto j : {c,d}) {
            auto res = solve(i,a+b-i,j,c+d-j);
            if (check(res,a,b,c,d)) { return res; }
            res = solve(j,c+d-j,i,a+b-i);
            if (check(res,a,b,c,d)) { return res; }
        }
    }
    assert(false);
}

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    int x1, y1, x2, y2, x3, y3, x4, y4;
    while (std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4) {
        Point a(x1,y1), b(x2,y2), c(x3,y3), d(x4,y4);
        if (a == b && a == c && a == d) { break; }
        auto res = brute(a,b,c,d);
        for (auto it : {res.A.p, res.B.p, res.C.p}) { std::cout << it << ' '; }
        std::cout << std::endl;
    }
    return 0;
}