// Первый элемент, не меньший x, в C++

#include <iostream>
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

    // Ищем минимальный индекс, на котором a[index] >= x
    int left = 0;
    int right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (a[mid] < x) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    // Выводим позицию и значение найденного элемента или -1
    if (left == n) {
        cout << -1 << '\n';
    } else {
        cout << left << ' ' << a[left] << '\n';
    }
}