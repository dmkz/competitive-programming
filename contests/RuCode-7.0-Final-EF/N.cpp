#include <bits/stdc++.h>
using ld = long double;
using namespace std;
int main() {
    int w, h; cin >> w >> h;
    ld d; cin >> d;
    // x^2+y^2=d^2 --- d это гипотенуза в прямоугольном треугольнике с катетами x и y*h
    // мы не знаем x и y, но знаем, что они относятся друг к другу как w к h
    // x/y=w/h=A => x = A*y --- подставим в уравнение и найдём y
    // (A^2+1)y^2=d^2
    ld A = ld(w)/h;
    ld y = d / sqrtl(A*A+1);
    // теперь мы знаем сколько пикселей в дюйме (h/y), это и есть ответ
    cout << fixed << setprecision(12);
    cout << h/y << endl;
}
