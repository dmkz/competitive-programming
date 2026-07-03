// Сортировка массива с компаратором в C++

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Чтение массива
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Сортируем по возрастанию абсолютного значения,
    // а при равенстве модулей — по самому числу
    sort(a.begin(), a.end(), [](int x, int y) {
        if (abs(x) != abs(y)) {
            return abs(x) < abs(y);
        }
        return x < y;
    });

    // Вывод результата
    for (int x : a) {
        cout << x << ' ';
    }
    cout << '\n';
}