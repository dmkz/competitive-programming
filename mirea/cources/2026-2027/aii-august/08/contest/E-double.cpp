// Codeforces: OK, 765 мс
// Яндекс.Контест: OK, 243 мс
#include <bits/stdc++.h>
using namespace std;
// геометрия: решаем специально в типе "double", чтобы убедиться, что стандартный тип заходит
using ld = double;
const ld EPS = 1e-15;
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
// проверка, находится ли точка P внутри треугольника ABC: сравниваем ориентацию векторов
bool insideTriangle(Pt P, Pt A, Pt B, Pt C) {
    return cross(B-A, P-A) >= 0 && cross(C-B, P-B) >= 0 && cross(A-C, P-C) >= 0;
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
    // функция проверки, покрывает ли треугольник все точки через t секунд?
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
    // бинарный поиск по ответу, потому что непонятно, какую величину взять за high
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