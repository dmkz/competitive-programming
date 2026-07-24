// Пример: все правильные скобочные последовательности из n пар скобок.
// Здесь допустимый префикс — тот, у которого число ')' не превосходит число '('.

#include <iostream>
#include <string>

using namespace std;

string current;

// Строим только те префиксы, которые ещё можно продолжить до правильной скобочной последовательности.
void dfs(int open_used, int close_used, int n) {
    if (open_used == n && close_used == n) {
        // Построили полную правильную последовательность.
        cout << current << '\n';
        return;
    }

    if (open_used < n) {
        // Всегда можно добавить ещё одну открывающую скобку, если лимит не исчерпан.
        current += '(';
        dfs(open_used + 1, close_used, n);
        current.pop_back();
    }

    if (close_used < open_used) {
        // Закрывающую скобку добавляем только к допустимому префиксу.
        current += ')';
        dfs(open_used, close_used + 1, n);
        current.pop_back();
    }
}

int main() {
    int n;
    // Считываем число пар скобок и запускаем перебор из пустого префикса.
    cin >> n;

    dfs(0, 0, n);
    return 0;
}