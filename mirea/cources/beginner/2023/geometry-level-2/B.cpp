#include <bits/stdc++.h>
using namespace std;
using ld = long double;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем данные
    ld x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    // выводим ответ (см. чертёж)
    cout << fixed << setprecision(12);
    cout << x1 + (x2 - x1) / (1 + y2 / y1) << endl;
}
