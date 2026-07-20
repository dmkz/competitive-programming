// Пример: удаление повторов в отсортированном массиве двумя указателями.
// Ввод: n и отсортированный массив a.
// Вывод: число различных значений и сами значения.

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int write = 0;
    // Один указатель читает массив, второй показывает место для следующего нового значения.
    for (int read = 0; read < n; read++) {
        if (read == 0 || a[read] != a[write - 1]) {
            // Переносим очередное новое значение в начало массива.
            a[write] = a[read];
            write++;
        }
    }

    a.resize(write);

    cout << a.size() << '\n';
    for (int i = 0; i < (int)a.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';

    return 0;
}