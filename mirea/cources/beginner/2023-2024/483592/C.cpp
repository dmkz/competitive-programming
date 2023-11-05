#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // в данном случае квадрат в круге это четыре равных прямоугольных треугольника
    // с катетами, равными r, поэтому площадь равна 4 * (0.5*r^2)
    long double r; cin >> r;
    cout << fixed << setprecision(12);
    cout << 2 * r * r << endl;
}
