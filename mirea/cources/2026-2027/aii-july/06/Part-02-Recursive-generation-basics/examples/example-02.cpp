// Пример: все строки длины n из цифр 0, 1, 2 через рекурсию.
// На каждой позиции можно дописать одну из трёх цифр.

#include <iostream>
#include <string>

using namespace std;

int n;
string current;

// Рекурсивно достраиваем строку из цифр 0, 1, 2.
void dfs(int pos) {
    if (pos == n) {
        // Построили полную строку.
        cout << current << '\n';
        return;
    }

    // На позицию pos по очереди ставим все допустимые цифры.
    for (char digit = '0'; digit <= '2'; digit++) {
        current += digit;
        dfs(pos + 1);
        current.pop_back();
    }
}

int main() {
    // Считываем длину строки и запускаем обход из пустого префикса.
    cin >> n;
    dfs(0);
    return 0;
}