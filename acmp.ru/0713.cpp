/*
    "Булева функция": динамическое программирование по профилю, O(n)
*/

#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>

int main() {
    int n;
    scanf("%d", &n);
    
    std::vector<int> f(4);
    for (int i = 0; i < 4; ++i) {
        char c;
        scanf(" %c", &c);
        f[i] = (c - '0');
    }
    
    std::vector<std::vector<int>> max1(2, std::vector<int>(n, -1));
    std::vector<std::vector<int>> from(2, std::vector<int>(n, -1));
    // Инициализация:
    max1[0][0] = 0;
    max1[1][0] = 1;
    // Динамика на префиксе:
    for (int i = 1; i < n; ++i) {
        for (int mask = 0; mask < 4; ++mask) {
            int prev = (mask >> 1) & 1;
            int curr = (mask >> 0) & 1;            
            if (max1[prev][i-1] == -1) {
                continue;
            }
            if (max1[f[mask]][i] < max1[prev][i-1] + (curr == 1)) {
                max1[f[mask]][i] = max1[prev][i-1] + (curr == 1);
                from[f[mask]][i] = mask;
            }
        }
    }
    
    if (max1[1][n-1] == -1) {
        printf("No solution");
        return 0;
    }
    
    // Формирование ответа:
    std::string answ;
    int value = 1;
    for (int i = n-1; i > 0; --i) {
        answ.push_back(((from[value][i] >> 0) & 1) + '0');
        value = (from[value][i] >> 1) & 1;
    }
    answ.push_back(value+'0');
    std::reverse(answ.begin(), answ.end());
    
    // Вывод ответа:
    printf("%s", answ.c_str());
    
    return 0;
}