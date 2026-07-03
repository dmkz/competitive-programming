// Нахождение минимума и максимума в C++

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Чтение размера массива и его элементов
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (a.empty()) {
        return 0;
    }

    // Поиск минимума и максимума вручную
    int mn = a[0];
    int mx = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < mn) {
            mn = a[i];
        }
        if (a[i] > mx) {
            mx = a[i];
        }
    }

    // Поиск минимума и максимума через std::minmax_element
    auto [mn_it, mx_it] = minmax_element(a.begin(), a.end());

    // Вывод ответа
    if (mn != *mn_it || mx != *mx_it) {
        return 1;
    }
    cout << mn << ' ' << mx << '\n';
}