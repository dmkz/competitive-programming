#include <bits/stdc++.h>
int main() {
    int n; std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    // Рассматриваем тройки соседей слева-направо.
    // Нас интересуют тройки {1, 0, 1}
    // В них надо заменять самую правую единицу на ноль
    // Это оптимальный выбор в данной ситуации и в будущем
    int k = 0;
    for (int i = 1; i + 1 < n; i++) {
        if (a[i-1] == 1 && a[i] == 0 && a[i+1] == 1) {
            a[i+1] = 0;
            k++;
        }
    }
    std::cout << k << std::endl;
}