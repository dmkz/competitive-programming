#include <bits/stdc++.h>
using namespace std;
int main() {
    // читаем координаты точек на плоскости:
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    // читаем возможные диагональные шаги:
    int x, y;
    cin >> x >> y;
    // смещаем центр проскости в (x1, y1)
    const int dx = abs(x2-x1);
    const int dy = abs(y2-y1);
    // теперь нам надо проверить, можно ли дойти из (0, 0) в (x, y)
    // возможные ходы:
    // (+x, +y)
    // (+x, -y)
    // (-x, +y)
    // (-x, -y)
    // применяя бесконечное число ходов, мы можем посетить клетки вида
    // (p * x, q * y)
    // так как каждый ход меняет чётность p и q на противоположную,
    // то (p % 2) == (q % 2) - оба чётные либо оба нечётные
    // надо проверить, что разность делится на возможные ходы и
    // результаты деления имеют одинаковую чётность
    const int p = dx / x;
    const int q = dy / y;
    const bool isDivisible = (p * x == dx && q * y == dy);
    const bool isEqualParity = (p % 2 == q % 2);
    const bool yes = isDivisible && isEqualParity;
    cout << (yes ? "YES\n" : "NO\n");
}