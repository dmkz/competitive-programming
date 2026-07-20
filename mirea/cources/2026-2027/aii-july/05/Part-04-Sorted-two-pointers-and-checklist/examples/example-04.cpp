// Пример: слияние двух отсортированных массивов в один.
// Ввод: n, m и два массива a и b, уже отсортированные по неубыванию.
// Вывод: объединённый отсортированный массив.

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int j = 0; j < m; j++) {
        cin >> b[j];
    }

    vector<int> merged;
    merged.reserve(n + m);

    int i = 0;
    int j = 0;
    while (i < n && j < m) {
        if (a[i] <= b[j]) {
            // Берём меньший текущий элемент из первого массива.
            merged.push_back(a[i]);
            i++;
        } else {
            // Берём меньший текущий элемент из второго массива.
            merged.push_back(b[j]);
            j++;
        }
    }

    while (i < n) {
        merged.push_back(a[i]);
        i++;
    }
    while (j < m) {
        merged.push_back(b[j]);
        j++;
    }

    for (int k = 0; k < (int)merged.size(); k++) {
        if (k > 0) {
            cout << ' ';
        }
        cout << merged[k];
    }
    cout << '\n';

    return 0;
}