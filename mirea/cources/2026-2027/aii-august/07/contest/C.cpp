#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = double; // используем "double", чтобы убедиться, что 64-битный тип заходит
// Структура данных для точки:
struct Pt {
    ll x, y;
    Pt operator-(const Pt &p) const {
        return {x - p.x, y - p.y};
    }
};
// скалярное произведение:
ll dot(Pt a, Pt b) {
    return a.x * b.x + a.y * b.y;
}
// векторное произведение:
ll cross(Pt a, Pt b) {
    return a.x * b.y - a.y * b.x;
}
// угол между двумя векторами:
ld angle(Pt a, Pt b) {
    return atan2(abs(cross(a,b)),dot(a,b));
}
// решение:
void solve() {
    // читаем данные:
    int n; cin >> n;
    vector<int> x(n+2), y(n+2);
    for (auto &it : x) cin >> it;
    for (auto &it : y) cin >> it;
    // положение Олега:
    Pt O = {x[n+1], y[n+1]};
    ld sum = 0;
    for (int i = 1; i <= n; i++) {
        // наше предыдущее положение:
        Pt A = {x[i-1], y[i-1]};
        // наше текущее положение:
        Pt B = {x[i], y[i]};
        // Олег поворачивает свой прицел в треугольнике OAB: было OA, стало OB.
        sum += angle(B - O, A - O);
    }
    // выводим ответ:
    cout << fixed << setprecision(12) << sum << '\n';
}
main() {
    int tt = 1; cin >> tt;
    while (tt --> 0) solve();
}