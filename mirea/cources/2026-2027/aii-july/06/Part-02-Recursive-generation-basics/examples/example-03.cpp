// Пример: все перестановки чисел от 1 до n через used[].
// used[x] показывает, стоит ли число x + 1 уже в текущем префиксе.

#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> current;
vector<int> used;

// Печатаем одну готовую перестановку.
void print_permutation() {
    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << current[i];
    }
    cout << '\n';
}

// Рекурсивно заполняем перестановку слева направо.
void dfs(int pos) {
    if (pos == n) {
        // Построили полную перестановку.
        print_permutation();
        return;
    }

    // На позицию pos пробуем поставить любое свободное число.
    for (int value = 1; value <= n; value++) {
        if (used[value - 1]) continue;

        // Добавляем свободное число в префикс.
        used[value - 1] = 1;
        current.push_back(value);
        dfs(pos + 1);

        // Откатываем состояние перед следующей веткой.
        current.pop_back();
        used[value - 1] = 0;
    }
}

int main() {
    // Считываем n, готовим массив used[] и запускаем обход.
    cin >> n;
    used.assign(n, 0);
    dfs(0);
    return 0;
}