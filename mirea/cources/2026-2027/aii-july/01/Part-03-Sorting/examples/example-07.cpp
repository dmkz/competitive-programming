// Сортировка массива по возрастанию и убыванию в C++

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

void print_vector(const vector<int>& a) {
    for (int x : a) {
        cout << x << ' ';
    }
    cout << '\n';
}

int main() {
    // Чтение массива и подготовка копий для разных вариантов сортировки
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> asc = a;
    vector<int> desc_by_reverse_iterators = a;
    vector<int> desc_by_comparator = a;

    // Сортировка по возрастанию и двумя способами по убыванию
    sort(asc.begin(), asc.end());
    sort(desc_by_reverse_iterators.rbegin(), desc_by_reverse_iterators.rend());
    sort(desc_by_comparator.begin(), desc_by_comparator.end(), greater<int>());

    // Вывод результата
    print_vector(asc);
    print_vector(desc_by_reverse_iterators);
    print_vector(desc_by_comparator);
}