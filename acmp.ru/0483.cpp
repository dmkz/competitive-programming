/*
    Главная проблема - второй шаг. Если делать явно, то асимптотика O(n^2)
    Проанализиурем сдвиги на примере 1001:
    1001
    0011
    0110
    1100
    ----
    1110
    
    Получается, что каждый единичный разряд побывает в каждом разряде.
    В итоге нужно посчитать следующую сумму:
    n1 + n1 * 2 + n1 * 4 + n1 * 8 + ...
    Это можно сделать за O(n)
*/

#include <stdio.h>
#include <string>
#include <algorithm>

int main() {
    int len; 
    scanf("%d", &len);
    
    char buf[1+100000]; 
    scanf("%100000s", buf);
    std::string s(buf);
    std::reverse(s.begin(), s.end());
    
    // Подсчет количества единичных битов:
    int n1 = 0;
    for (auto it : s) n1 += (it == '1');
    
    // Суммирование сдвигов:
    int rem = 0;
    for (auto& it : s) {
        rem += n1;
        it = (rem % 2) + '0';
        rem /= 2;
    }
    
    // Логическое отрицание
    for (auto& it : s) it = char('1' - it + '0');
    
    // Прибавление 1
    rem = 1;
    for (auto& it : s) {
        rem += (it - '0');
        it = rem % 2 + '0';
        rem /= 2;
    }
    
    // Отбрасывание ведущих нулей:
    while (s.back() == '0' && (int)s.size() > 1) s.pop_back();
    
    // Вывод результата:
    std::reverse(s.begin(), s.end());
    printf("%s\n", s.c_str());

    return 0;
}