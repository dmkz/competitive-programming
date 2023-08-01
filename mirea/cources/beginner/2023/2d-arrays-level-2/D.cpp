#include <iostream>
#include <vector>
#include <cassert>

int main() {
    // ромб n x n работает и удовлетворяет условию:
    // ..*..
    // .***.
    // *****
    // .***.
    // ..*..
    // все нечётные числа ставим в ромб, их как раз (n^2+1)/2
    int n; std::cin >> n;
    std::vector answ(n, std::vector<int>(n));
    // формируем векторы из нечётных и чётных чисел:
    std::vector<int> odd,even;
    for (int i = 1; i <= n * n; ++i) {
        if (i % 2 == 0)
            even.push_back(i);
        else
            odd.push_back(i);
    }
    // заполняем нечётные числа
    // в i-й строке в ромб входят столбцы, если мы отступим
    // i влево и i вправо от середины
    for (int i = 0; i < n / 2; ++i) {
        for (int j = n / 2 - i; j <= n / 2 + i; ++j) {
            // ставим очередное нечётное число в верхнюю половину:
            assert(!odd.empty());
            answ[i][j] = odd.back();
            odd.pop_back();
            // ставим в нижнюю половину ромба (симметричную ей)
            assert(!odd.empty());
            answ[n-i-1][j] = odd.back();
            odd.pop_back();
        }
    }
    // заполняем среднюю строку нечётными числами (там нет симметрии):
    for (int j = 0; j < n; ++j) {
        assert(!odd.empty());
        answ[n/2][j] = odd.back();
        odd.pop_back();
    }
    // все оставшиеся числа заполняем чётными. незаполненные клетки равны
    // нулю, поэтому заменяем их чётными числами
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (answ[i][j] == 0) {
                assert(!even.empty());
                answ[i][j] = even.back(); 
                even.pop_back();
            }
            std::cout << answ[i][j] << ' ';
        }
        std::cout << '\n';
    }
    
    return 0;
}