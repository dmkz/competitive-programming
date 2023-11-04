#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using ld = long double;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // рассмотрите систему линейных уравнений, где неизвестные - то, сколько надо
    // сделать нажатий на каждую кнопку. Например, при n = 4 будет:
    // -1 +1 +1 +1     x1   b1 - a1
    // +1 -1 +1 +1  *  x2 = b2 - a2
    // +1 +1 -1 +1     x3   b3 - a3
    // +1 +1 +1 -1     x4   b4 - a4
    
    // Прибавим все строки к последней:
    // -1 +1 +1 +1     x1   b1 - a1
    // +1 -1 +1 +1  *  x2 = b2 - a2
    // +1 +1 -1 +1     x3   b3 - a3
    // +2 +2 +2 +2     x4   sum(bi - ai)
    
    // Поделим последнюю на (n-2) и вычтем из всех остальных:
    // -2  0  0  0     x1   b1 - a1 - sum(bi - ai) / (n-2)
    //  0 -2  0  0  *  x2 = b2 - a2 - sum(bi - ai) / (n-2)
    //  0  0 -2  0     x3   b3 - a3 - sum(bi - ai) / (n-2)
    // +1 +1 +1 +1     x4   sum(bi - ai) / (n-2)
    
    // Теперь мы можем найти x1, x2, x3, а затем и x4
    
    // Читаем коэффициенты системы линейных уравнений:
    int n; cin >> n;
    ld sumA{}, sumB{};
    vector<int> a(n), b(n);
    vector<ld> coeff(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        coeff[i] -= a[i];
        sumA += a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        coeff[i] += b[i];
        sumB += b[i];
    }
    if (n == 1) { // крайний случай с всего одной кнопкой
        cout << (int)(-coeff[0]) << endl;
        return 0;
    }
    if (n == 2) { // две кнопки
        coeff[1] += coeff[0];
        if (coeff[1] != 0) {
            cout << -1 << endl;
            return 0;
        }
        // -x0 + x1 = c0
        // x1 = c0 + x0
        // положим x0 = 0, тогда x1 = c0
        // НЕЛЬЗЯ ВЫВОДИТЬ ОТРИЦАТЕЛЬНЫЕ ЧИСЛА
        int64_t x0 = 0, x1 = coeff[0];
        if (x1 < 0) {
            x0 -= x1;
            x1 = 0;
        }
        cout << x0 << ' ' << x1 << endl;
        return 0;
    }
    // находим последний коэффициент после прибавления всех строк к последней:
    ld sub = (coeff[n-1] = (sumB - sumA) / (n-2));
    for (int i = 0; i + 1 < n; i++) {
        // вычитаем последнюю строчку из каждой:
        coeff[i] -= sub;
        // находим i-й коэффициент путём деления на диагональный элемент:
        coeff[i] /= (-2);
        // вычитаем найденный ответ из последней строчки:
        coeff[n-1] -= coeff[i];
    }
    // мы нашли решение системы уравнений. Приведём к целым числам и сделаем проверку
    bool ok = 1;
    vector<int64_t> solution(all(coeff));
    int64_t total = accumulate(all(solution), 0LL);
    for (int i = 0; i < n; i++) {
        int64_t value = a[i];
        value -= solution[i];
        value += (total - solution[i]);
        ok &= (value == b[i] && solution[i] >= 0);
        // НЕЛЬЗЯ ВЫВОДИТЬ ОТРИЦАТЕЛЬНЫЕ ЧИСЛА
    }
    if (!ok) {
        cout << -1 << endl;
        return 0;
    }
    for (auto it : solution)
        cout << it << ' ';
}
