// Codeforces: OK, 781 мс
// Яндекс.Контест: OK, 295 мс
#include <bits/stdc++.h>
using namespace std;
// геометрия: решаем специально в типе "long double", чтобы повысить точность
using ld = long double;
const ld EPS = 1e-18L;
// стандартное сравнение двух чисел по относительной или абсолютной ошибке:
bool isAlmostEqual(ld a, ld b, ld eps = EPS) {
    return abs(a-b) <= eps * std::max<ld>({1, abs(a), abs(b)});
}
// структура под геометрический вектор и операции с ним:
struct Vec {
    ld x, y;
    Vec(ld x_ = 0, ld y_ = 0) : x(x_), y(y_) { }
    Vec operator+(const Vec &v) const {
        return Vec(x + v.x, y + v.y);
    }
    Vec operator-(const Vec &v) const {
        return Vec(x - v.x, y - v.y);
    }
    Vec operator-() const {
        return Vec(-x, -y);
    }
    Vec operator*(const ld a) const {
        return Vec(a * x, a * y);
    }
    Vec operator/(const ld a) const {
        return Vec(x / a, y / a);
    }
};
// скалярное произведение:
ld dot(Vec a, Vec b) {
    return a.x * b.x + a.y * b.y;
}
// длина вектора:
ld norm(Vec a) {
    return sqrt(dot(a, a));
}
// векторное произведение:
ld cross(Vec a, Vec b) {
    return a.x * b.y - a.y * b.x;
}
using Pt = Vec;
// удвоенная площадь треугольника:
ld square(Pt a, Pt b, Pt c) {
    return abs(cross(b - a, c - a));
}
// проверка, находится ли точка P внутри треугольника ABC: сравниваем площади
bool insideTriangle(Pt P, Pt A, Pt B, Pt C) {
    ld s1 = square(P, A, B) + square(P, A, C) + square(P, B, C);
    ld s2 = square(A, B, C);
    return isAlmostEqual(s1, s2);
}
// решение задачи:
void solve() {
    // читаем данные:
    int n; cin >> n;
    int xA, yA, xB, yB, xC, yC;
    cin >> xA >> yA >> xB >> yB >> xC >> yC;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    // Построение треугольника:
    Pt pa(xA, yA), pb(xB, yB), pc(xC, yC);
    Vec va = pa / norm(pa);
    Vec vb = pb / norm(pb);
    Vec vc = pc / norm(pc);
    // бинарный поиск по ответу:
    auto check = [&](ld t) -> bool {
        // Строим треугольник через t секунд:
        Pt A = pa + va * t;
        Pt B = pb + vb * t;
        Pt C = pc + vc * t;
        // Проверяем, что он поглотит все точки:
        for (int i = 0; i < n; i++)
            if (!insideTriangle(Pt(x[i], y[i]), A, B, C))
                return false;
        return true;
    };
    // Проблема: непонятно, какую величину взять за high
    // 1. находим первоначальные границы поиска: (low, high]
    ld low = 0, high = 1e-7;
    while (!check(high)) {
        low = high;
        high *= 2;
    }
    // 2. сужаем поиск:
    while (!isAlmostEqual(low, high, 1e-7)) {
        ld mid = (low + high) / 2;
        // Проверяем, что треугольник поглотит все точки:
        if (check(mid)) high = mid;
        else low = mid;
    }
    // выводим ответ:
    cout << fixed << setprecision(12) << (high + low) / 2 << '\n';
}
main() {
    int tt = 1; cin >> tt;
    while (tt --> 0) solve();
}