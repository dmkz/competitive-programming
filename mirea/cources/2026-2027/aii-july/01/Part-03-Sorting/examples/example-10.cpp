// Сортировка слиянием в C++

#include <iostream>
#include <vector>

using namespace std;

vector<int> merge_sort(const vector<int>& a) {
    if (a.size() <= 1) {
        return a;
    }

    int mid = (int)a.size() / 2;

    // Разбиваем массив на две половины и сортируем их отдельно
    vector<int> left(a.begin(), a.begin() + mid);
    vector<int> right(a.begin() + mid, a.end());
    left = merge_sort(left);
    right = merge_sort(right);

    // Сливаем две уже отсортированные половины в один отсортированный массив
    vector<int> merged;
    merged.reserve(a.size());

    int i = 0;
    int j = 0;
    while (i < (int)left.size() && j < (int)right.size()) {
        if (left[i] <= right[j]) {
            merged.push_back(left[i]);
            i++;
        } else {
            merged.push_back(right[j]);
            j++;
        }
    }

    // Добавляем оставшиеся элементы той половины, которая ещё не закончилась
    while (i < (int)left.size()) {
        merged.push_back(left[i]);
        i++;
    }
    while (j < (int)right.size()) {
        merged.push_back(right[j]);
        j++;
    }

    return merged;
}

int main() {
    // Чтение массива и запуск сортировки
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    a = merge_sort(a);

    // Вывод отсортированного массива
    for (int x : a) {
        cout << x << ' ';
    }
    cout << '\n';
}