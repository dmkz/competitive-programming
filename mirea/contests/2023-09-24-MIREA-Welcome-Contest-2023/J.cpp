#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld pi = acos(ld(-1));

ld x(ld R, ld t) { return R * cos(2*pi*t); }
ld y(ld R, ld t) { return R * sin(2*pi*t); }
ld z(ld  , ld t) { return t; }

// считаем длину супер мелкого отрезка 10^(-12) и умножаем её на 10^12
// чтобы посчитать длину одного лестничного пролёта
ld solve(ld R, ld eps = 1e-12L) {
    ld dx = x(R, eps) - x(R, 0);
    ld dy = y(R, eps) - y(R, 0);
    ld dz = z(R, eps) - z(R, 0);
    ld dist = sqrtl(dx*dx+dy*dy+dz*dz);
    return dist/eps;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(9);
    int tt; cin >> tt;
    while (tt --> 0) {
        int t1, t2; double R;
        cin >> t1 >> t2 >> R;
        // длину одного лестничного пролёта умножаем на число этажей
        cout << (t2 - t1) * solve(R) << endl;
    }
}