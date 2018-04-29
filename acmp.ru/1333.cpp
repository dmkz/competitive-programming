/*
    Бинарный поиск по правому концу. 
    Для фиксированного правого конца можно решить трехдиагональную систему методом прогонки.
*/
#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>

typedef long double Real;

std::vector<Real> solve_tridiag(int n, Real L, Real R) {
// n - кол-во узлов, L и R - высоты левого и правого концов соответственно
    if (n == 3) {
        return {L, (L+R)/2-1, R};
    }
    /*
        Общий вид уравнений: 
            x[i-1] - 2 x[i] + x[i+1] = 2
        
        Для метода прогонки:            
            a[i] * x[i-1] + c[i] * x[i] + b[i] * x[i+1] = f[i]
        
        При i = 1: 
            -2 * x[i] + x[i+1] = 2 - L
        
        При i = n-2: 
            x[i-1] - 2 * x[i] = 2 - R
    */
    
    // Массивы коэффициентов системы:
    std::vector<Real> a(n-2, 1), b(n-2, 1), c(n-2, -2), f(n-2, 2); 
    a.front() = b.back() = 0;
    f.front() -= L;
    f.back() -= R;
    
    // Прямой ход - вычисляем прогоночные коэффициенты:
    std::vector<Real> alpha{0}, beta{0};
    alpha.push_back(-b[0] / c[0]);
    beta.push_back(f[0] / c[0]);
    for (int i = 1; i < (int)c.size(); ++i) {
        assert(i == (int)alpha.size()-1);
        auto q = a[i] * alpha[i] + c[i];
        alpha.push_back(-b[i] / q);
        beta.push_back((f[i] - a[i] * beta[i]) / q);
    }
    
    // Обратный ход - вычисление решения системы:
    std::vector<Real> x(n-2);
    x[n-3] = (f[n-3] - a[n-3] * beta[n-3]) / (c[n-3] + a[n-3] * alpha[n-3]);
    for (int i = n-4; i >= 0; --i) {
        x[i] = alpha[i+1] * x[i+1] + beta[i+1];
    }
    x.insert(x.begin(), L);
    x.insert(x.end(), R);
    return x;
}

int main() {
    int n; Real L;
    std::cin >> n >> L;
    
    Real low = -1, high = 1000*1000;
    const Real eps = 1e-3;
    while (high - low > eps) {
        auto mid = (low + high) / 2;
        auto x = solve_tridiag(n, L, mid);
        bool flag = true;
        for (auto it : x) {
            if (it <= 0) {
                flag = false;
                break;
            }
        }
        if (flag) {
            high = mid;
        } else {
            low = mid;
        }
    }
    std::cout << std::fixed << std::setprecision(2) << high << std::endl;
    return 0;
}