#include <bits/stdc++.h>
using namespace std;
int main() {
    // читаем границы отрезка:
    int L1, R1, L2, R2;
    cin >> L1 >> R1 >> L2 >> R2;
    // находим границы пересечения двух отрезков:
    const int L = max(L1, L2);
    const int R = min(R1, R2);
    // проверяет длину отрезка на положительность:
    if (L >= R) cout << "-1";
    else cout << L << ' ' << R;
}