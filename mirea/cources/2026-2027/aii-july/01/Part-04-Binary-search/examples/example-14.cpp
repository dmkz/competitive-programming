// Максимальный элемент, меньший x, в C++

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    // Чтение отсортированного массива и значения x
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int x;
    cin >> x;

    // Ручной бинарный поиск последнего индекса, на котором a[index] < x
    int left = -1;
    int right = n;
    while (right - left > 1) {
        int mid = left + (right - left) / 2;
        if (a[mid] < x) {
            left = mid;
        } else {
            right = mid;
        }
    }

    // Через lower_bound достаточно взять предыдущий элемент
    auto it = lower_bound(a.begin(), a.end(), x);
    bool has_manual = left != -1;
    bool has_library = it != a.begin();

    if (has_manual != has_library) {
        return 1;
    }
    if (has_manual && a[left] != *prev(it)) {
        return 1;
    }

    // Выводим ответ двумя способами
    if (!has_manual) {
        cout << "NO\n";
        cout << "NO\n";
    } else {
        cout << a[left] << '\n';
        cout << *prev(it) << '\n';
    }
}