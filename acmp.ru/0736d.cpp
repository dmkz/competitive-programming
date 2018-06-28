/*
    "Удаление": динамическое программирование, O(n)
*/

#include <stdio.h>
#include <vector>

int main() {
    int n, k, q;
    scanf("%d %d %d", &n, &k, &q);
    
    std::vector<int> answer(1+n), stages(1+n), erased(1+n);
    
    // Вычисление ответа для элементов, удаленных на первой итерации:
    for (int i = 1; i * k <= n; ++i) {
        answer[i * k] = i;
    }
    
    // Находим, куда перейдут элементы после удаления на последующих итерациях:
    for (int curr = k; curr <= n; ++curr) {
        if (answer[curr] == 0) {
            int prev = curr - curr / k;
            answer[curr] = answer[prev];
            stages[curr] = stages[prev] + 1;
        }
    }
    
    // Предподсчитаем количество удаленных элементов после каждой итерации:
    for (int i = 1; i <= n; ++i) {
        erased[i] = erased[i-1] + (n - erased[i-1]) / k;
    }
    
    // Отвечаем на запросы:
    while (q--) {
        int item;
        scanf("%d", &item);
        printf("%d\n", answer[item] + erased[stages[item]]);
    }
    
    return 0;
}