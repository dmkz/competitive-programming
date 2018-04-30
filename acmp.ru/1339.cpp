/*
    Метод прогонки. При фиксированных концах находим первое число фибоначчи слева от правого конца.
    От найденных двух соседних чисел Фибонначи линейно получаем нужное.
    Для надежности, чтобы избежать переполнения, решаем в вещественных числах.
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>

typedef long double Real;

std::vector<Real> solve_tridiag(int n, Real L, Real R) {
// n - расстояние между индексами чисел Фибоначчи, L и R - числа фибоначчи на концах
    if (n == 1) {
        return {L, R};
    }
    if (n == 2) {
        return {L, R-L, R};
    }
    /*
        Общий вид уравнений: 
            x[i-1] + x[i] - x[i+1] = 0
        
        Для метода прогонки:            
            a[i] * x[i-1] + c[i] * x[i] + b[i] * x[i+1] = f[i]
        
        При i = 1: 
            x[i] - x[i+1] = - L
        
        При i = n-1: 
            x[i-1] + x[i] = R
    */
    
    // Массивы коэффициентов системы:
    std::vector<Real> a(n-1, 1), b(n-1, -1), c(n-1, 1), f(n-1, 0); 
    a.front() = b.back() = 0;
    f.front() -= L;
    f.back() += R;
    
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
    std::vector<Real> x(n-1);
    x[n-2] = (f[n-2] - a[n-2] * beta[n-2]) / (c[n-2] + a[n-2] * alpha[n-2]);
    for (int i = n-3; i >= 0; --i) {
        x[i] = alpha[i+1] * x[i+1] + beta[i+1];
    }
    x.insert(x.begin(), L);
    x.insert(x.end(), R);
    return x;
}

Real solve(int i_min, Real f_min, int i_max, Real f_max, int index) {
    auto f = solve_tridiag(i_max-i_min, f_min, f_max);
    if (index >= i_max) {
        Real prev = f[(int)f.size()-2];
        Real curr = f[(int)f.size()-1];
        for (int i = i_max; i < index; ++i) {
            Real next = prev + curr;
            prev = curr;
            curr = next;
        }
        return curr;
    } else {
        Real curr = f[(int)f.size()-1];
        Real next = curr + f[(int)f.size()-2];
        for (int i = i_max; i > index; --i) {
            Real prev = next-curr;
            next = curr;
            curr = prev;
        }
        return curr;
    }
}

int main() {
    int i1, i2, i3;
    Real f1, f2; 
    std::cin >> i1 >> f1 >> i2 >> f2 >> i3;
    
    if (i2 < i1) {
        std::swap(i1, i2);
        std::swap(f1, f2);
    }
    
    std::cout << std::fixed << std::setprecision(0) << solve(i1, f1, i2, f2, i3) << std::endl;
    
    return 0;
}