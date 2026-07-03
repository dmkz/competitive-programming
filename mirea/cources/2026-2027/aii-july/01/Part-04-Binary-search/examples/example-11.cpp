// Ручной бинарный поиск элемента в C++

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

    // Поддерживаем текущий отрезок поиска и каждый раз отбрасываем половину
    int left = 0;
    int right = n - 1;
    int answer = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid] == x) {
            answer = mid;
            break;
        }
        if (a[mid] < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // Выводим индекс найденного элемента или -1
    cout << answer << '\n';
}