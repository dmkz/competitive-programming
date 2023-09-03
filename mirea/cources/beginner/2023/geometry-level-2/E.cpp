#include <bits/stdc++.h>
using namespace std;
using Real = long double;
using Complex = complex<Real>;
const Real PI = acos(Real(-1)); // число пи это acos от -1
namespace std {
    // оператор сравнения комплексных чисел по полярному углу:
    bool operator<(const Complex& z1, const Complex& z2) {
        return arg(z1) < arg(z2);
    }
}
int main() {
    // читаем точки как комплексные числа и запоминаем номер
    // каждой точки (это надо для вывода ответа)
    int n; cin >> n;
    vector<Complex> a(n);
    map<Complex, int> id; // внутри используется оператор из 8-й строчки
    for (int i = 0,x,y; i < n; i++) {
        cin >> x >> y;
        a[i] = {x,y};
        id[a[i]] = i+1;
    }
    // сортируем комплексные числа по полярному углу
    sort(a.begin(), a.end()); // внутри используется оператор из 8-й строчки
    // дублируем начальную точку в конец:
    a.push_back(a.front());
    // ответ это тройка (угол, индекс1, индекс2)
    tuple answ{2*PI,0,0};
    for (int i = 0; i + 1 < (int)a.size(); i++) {
        // перебираем соседние точки A и B
        Complex A = a[i], B = a[i+1];
        // угол между векторами это разница аргументов
        Real angle = arg(B)-arg(A);
        // если отрицательный, то прибавим 2 * PI
        if (angle < 0) angle += 2 * PI;
        // обновляем ответ:
        answ = min(answ, make_tuple(angle,id[A],id[B]));
    }
    // выводим номера векторов в качестве ответа (второй и третий аргумент тройки)
    cout << get<1>(answ) << ' ' << get<2>(answ) << endl;
}