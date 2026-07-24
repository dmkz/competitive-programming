// Пример: все двоичные строки длины n без двух единиц подряд.
// Отсечение здесь очень простое: после символа '1' нельзя ставить ещё одну '1'.

#include <iostream>
#include <string>

using namespace std;

int n;
string current;

// Строим строку слева направо и не создаём ветви, где подряд идут две единицы.
void dfs(int pos) {
    if (pos == n) {
        cout << current << '\n';
        return;
    }

    // Ветка с добавлением нуля всегда разрешена.
    current += '0';
    dfs(pos + 1);
    current.pop_back();

    // Единицу можно поставить только после пустого префикса или после символа, отличного от '1'.
    if (current.empty() || current.back() != '1') {
        current += '1';
        dfs(pos + 1);
        current.pop_back();
    }
}

int main() {
    // Считываем длину строки и запускаем перебор из пустого префикса.
    cin >> n;
    dfs(0);
    return 0;
}