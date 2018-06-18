/*
    Решение использует тот факт, что функция ответа имеет порядок роста O(log(n)).
    
    Следовательно, значения f(n) и f(n+1) при n >= 2 отличаются не более, чем на единицу.
    
    Рассмотрим f(2) = 2 и разбиение на группы размера (part1 = 1, part2 = 1).
    
    Для следующего значения f(3) подойдет:
    
    а) либо разбиение на отрезки размера (part1+1, part2) = (2, 1), 
    б) либо разбиение на отрезки размера (part1, part2+1) = (1, 2).
    
    Из двух вариантов нужно выбрать лучший по значению функции f(3) на них.
    
    На практике проверяется, что это же свойство выполняется и на последующих значених.
    
    Следовательно, при переходе от f(n) с разбиением на отрезки (part1, part2) к f(n+1) мы должны рассмотреть два варианта:
    
    а) (part1+1, part2)
    б) (part1, part2+2)
    
    И выбрать среди них лучший.
    
    Предлагаемое решение использует O(n) времени и O(log(n)) памяти.
*/

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cassert>

int main() {
    int n;
    scanf("%d", &n);
    
    if (n == 0 || n == 1) {
        printf("0");
        return 0;
    }
    
    // [begin[y], after[y]) - полуинтервал значений, на котором функция f(n) = x
    std::vector<int> begin{0,2,2}, after{2,2,3}; 
    
    // Начинаем со значения f(2) = 2 и разбиения (1, 1)
    int part1 = 1, answ1 = 0, part2 = 1, answ2 = 0, answ = 2;
    
    for (int size = 3; size <= n; ++size) {
        // Рассматриваем вариант part1, part2++:
        part2++;
        while (after[answ2] == part2) ++answ2;
        int res1 = std::max(answ1+1, answ2+2);
        part2--;
        while (begin[answ2] > part2) --answ2;
        
        // Рассматриваем вариант part1++, part2:
        part1++;
        while (after[answ1] == part1) ++answ1;
        int res2 = std::max(answ1+1, answ2+2);
        part1--;
        while (begin[answ1] > part1) --answ1;
        
        // Выбираем лучший вариант:
        if (res1 <= res2) {
            answ = res1;
            ++part2;
            while (after[answ2] == part2) ++answ2;
        } else {
            answ = res2;
            ++part1;
            while (after[answ1] == part1) ++answ1;
        }
        
        // Если значение answ увеличилось, то добавляем новый интервал:
        if ((int)begin.size() <= answ) {
            begin.push_back(size);
            after.push_back(size);
        }
        
        // И, наконец, смещаем правую границу последнего интервала:
        after[answ]++;    
    }
    
    printf("%d", answ);
    
    return 0;
}