#include <bits/stdc++.h>
using namespace std;
using ld = long double;
ld ask(int x) {
    cout << "? " << x << endl;
    ld dist; cin >> dist;
    return dist;
}
int32_t main() {
    // S = (abc) / (4R) ==> R = (abc)/(4S)
    // из трех запросов узнаем стороны треугольника
    // опишем возле него окружность
    ld right = ask(0), left = ask(180), down = ask(270);
    ld a = left+right;
    ld b = sqrtl(left*left+down*down);
    ld c = sqrtl(right*right+down*down);
    ld S = a * down / 2;
    ld R = (a*b*c)/(4*S);
    cout << fixed << setprecision(0);
    cout << "! " << R << endl;
}
