// Пример: все двоичные строки длины n через рекурсию.
// На каждой позиции выбираем один из двух символов: '0' или '1'.

#include <iostream>
#include <string>

using namespace std;

int n;
string current;

// Рекурсивно достраиваем двоичную строку слева направо.
void dfs(int pos) {
    if (pos == n) {
        // Построили полную строку.
        cout << current << '\n';
        return;
    }

    // Ветка 1: ставим на позицию pos символ '0'.
    current += '0';
    dfs(pos + 1);
    current.pop_back();

    // Ветка 2: ставим на позицию pos символ '1'.
    current += '1';
    dfs(pos + 1);
    current.pop_back();
}

int main() {
    // Считываем длину строки и запускаем обход из пустого префикса.
    cin >> n;
    dfs(0);
    return 0;
}