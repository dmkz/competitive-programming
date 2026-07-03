// Сортировка слиянием через inplace_merge в C++

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void merge_sort(auto begin, auto end) {
    if (begin + 1 >= end) {
        return; // диапазон либо пуст, либо состоит из 1 элемента
    }

    // Делим диапазон пополам и отдельно сортируем обе половины
    auto mid = begin + (end - begin) / 2;
    merge_sort(begin, mid);
    merge_sort(mid, end);

    // Стандартная функция объединяет две соседние отсортированные части
    inplace_merge(begin, mid, end);
}

int main() {
    // Чтение массива и запуск сортировки
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    merge_sort(a.begin(), a.end());

    // Вывод отсортированного массива
    for (int x : a) {
        cout << x << ' ';
    }
    cout << '\n';
}