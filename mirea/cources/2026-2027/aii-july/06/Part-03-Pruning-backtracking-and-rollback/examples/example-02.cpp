// Пример: число перестановок чисел от 1 до n, в которых число i не стоит на позиции i.
// Откат обязателен: после каждой ветки снимаем used[] и убираем последнее число из префикса.

#include <iostream>
#include <vector>

#include <cmath>

using namespace std;

int n;
long long ways = 0;
vector<int> current;
vector<int> used;

// Строим перестановку слева направо и откатываем состояние после каждой ветки.
void dfs(int pos) {
    if (pos == n) {
        // Нашли одну полную подходящую перестановку.
        ways++;
        return;
    }

    for (int value = 1; value <= n; value++) {
        if (used[value - 1]) continue;

        // Не разрешаем числу value стоять на его собственной позиции.
        if (value == pos + 1) continue;

        // Занимаем число value и углубляемся.
        used[value - 1] = 1;
        current.push_back(value);
        dfs(pos + 1);

        // Откатываем все изменения перед следующей веткой.
        current.pop_back();
        used[value - 1] = 0;
    }
}

int main() {
    // Считываем n, обнуляем used[] и запускаем поиск.
    cin >> n;

    used.assign(n, 0);
    dfs(0);

    cout << ways << '\n';
    return 0;
}