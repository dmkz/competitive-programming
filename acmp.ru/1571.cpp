/*
    Решение задачи "1571. Великая таблица умножения" на acmp.ru.
    
    При помощи stdio.h:
    
    Чтение 64-битных целых чисел как строка в стиле си:
        Время: 0.436, Память: 2252 Кб
        
    Чтение 64-битных целых чисел как число %I64d:
        Время: 0.562, Память: 2252 Кб

    При помощи cstdio - TLE16 и TLE14 соответственно
    
    Потоки ввода/вывода:
    
    Чтение как long long:
        Время: 0.842, Память: 2252 Кб
        
    Чтение как строки в стиле си:
        Время: 0.436, Память: 2252 Кб
        
    Буфферизованный ввод:
        Время: 0.186, Память: 2252 Кб
        
    Чисел на входе: 500*500 = 250000   
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <string>

typedef long long ll;

// Функция проверки того, что двумерный массив a является фрагментом таблицы умножения:
bool solve(const std::vector<std::vector<ll>>& a) {
    const int nRows = (int)a.size();
    const int nCols = (int)a[0].size();
    if (nRows == 1 && nCols == 1) {
        return true;
    }
    ll start_j = -1, start_i = -1;
    if (nCols > 1) {
        start_j = a[0][1] - a[0][0];
    }
    if (nRows > 1) {
        start_i = a[1][0] - a[0][0];
    }
    if (nRows == 1) {
        if (start_j <= 0 || a[0][0] % start_j != 0) {
            return false;
        }
        start_i = a[0][0] / start_j;
    }
    if (nCols == 1) {
        if (start_i <= 0 || a[0][0] % start_i != 0) {
            return false;
        }
        start_j = a[0][0] / start_i;
    }
    if (start_i <= 0 || start_j <= 0) {
        return false;
    }
    assert(start_i > 0 && start_j > 0);
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            const ll nm = a[i][j], n = j+start_i, m = i+start_j;
            if (nm % n != 0 || nm % m != 0 || nm / n != m || nm / m != n) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nRows, nCols;
    std::cin >> nRows >> nCols;
    std::vector<std::vector<ll>> a(nRows, std::vector<ll>(nCols));
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            char buf[22];
            std::cin >> buf;
            a[i][j] = std::atoll(buf);
        }
    }
    std::cout << (solve(a) ? "true" : "false");
    return 0;
}