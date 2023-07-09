#include <bits/stdc++.h>
using namespace std;
using ld = long double;
int main()
{
    // зависимость ответа от расстояния: квадратическая
    // то есть, f(r) = C * r^2
    // в тесте из условия дано f(1) --> находим C = 0.916297857297023
    // теперь можем решить задачу:
    ld x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    ld r = hypotl(abs(x1-x2),abs(y1-y2));
    cout << fixed << setprecision(12);
    cout << r * r * 0.916297857297023 << '\n';
    return 0;
}
