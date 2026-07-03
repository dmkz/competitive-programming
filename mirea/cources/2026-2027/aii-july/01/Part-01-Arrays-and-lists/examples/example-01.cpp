// Основные операции с vector<int> в C++

#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Создание вектора фиксированной длины и заполнение по индексам
    int n = 5;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = (i + 1) * 10;
    }

    // Получение размера, чтение и изменение элемента
    int sz = (int)a.size();
    int x = a[2];
    a[2] = x + 5;

    // Создание пустого вектора и добавление элементов в конец
    vector<int> b;
    b.push_back(5);
    b.push_back(8);
    b.push_back(13);

    // Удаление последнего элемента и вывод результата
    b.pop_back();
    cout << "size = " << sz << '\n';

    cout << "a = ";
    for (int value : a) {
        cout << value << ' ';
    }
    cout << '\n';

    cout << "b = ";
    for (int value : b) {
        cout << value << ' ';
    }
    cout << '\n';
}