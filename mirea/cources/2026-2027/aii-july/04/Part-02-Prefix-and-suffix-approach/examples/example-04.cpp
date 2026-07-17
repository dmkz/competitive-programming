// Пример: минимум на каждом суффиксе.
// Ввод: n и массив чисел.
// Вывод: массив минимумов на суффиксах.

#include <algorithm>
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

    vector<int> suf_min(n);
    suf_min[n - 1] = a[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        suf_min[i] = min(a[i], suf_min[i + 1]);
    }

    for (int i = 0; i < n; i++) {
        if (i) {
            cout << ' ';
        }
        cout << suf_min[i];
    }
    cout << '\n';

    return 0;
}