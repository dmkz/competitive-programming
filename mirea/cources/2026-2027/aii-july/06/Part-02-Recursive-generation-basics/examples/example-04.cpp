// Пример: все подмножества множества {1, ..., n}.
// На каждом шаге рекурсия решает, брать текущий элемент или нет.

#include <iostream>
#include <vector>

using namespace std;

vector<int> current;

// Печатаем одно готовое подмножество в виде {1, 3, 5}.
void print_subset() {
    cout << '{';
    for (int i = 0; i < (int)current.size(); i++) {
        if (i) cout << ", ";
        cout << current[i];
    }
    cout << "}\n";
}

// Для каждого value решаем: брать его в подмножество или нет.
void dfs(int value, int n) {
    if (value > n) {
        // Построили одно полное подмножество.
        print_subset();
        return;
    }

    // Ветка 1: не берём value.
    dfs(value + 1, n);

    // Ветка 2: берём value.
    current.push_back(value);
    dfs(value + 1, n);
    current.pop_back();
}

int main() {
    int n;
    // Считываем n и запускаем перебор с первого числа.
    cin >> n;

    dfs(1, n);
    return 0;
}