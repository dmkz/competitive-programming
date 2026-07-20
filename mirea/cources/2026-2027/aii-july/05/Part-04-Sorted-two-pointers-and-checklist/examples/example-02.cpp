// Пример: пересечение двух массивов с учётом кратности.
// Ввод: n, m и два массива.
// Вывод: число общих элементов и сами общие элементы.

#include <algorithm>
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
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<int> common;
    int i = 0;
    int j = 0;
    // Сравниваем текущие элементы и двигаем тот указатель, где значение меньше.
    while (i < n && j < m) {
        if (a[i] == b[j]) {
            common.push_back(a[i]);
            i++;
            j++;
        } else if (a[i] < b[j]) {
            i++;
        } else {
            j++;
        }
    }

    cout << common.size() << '\n';
    for (int k = 0; k < (int)common.size(); k++) {
        if (k > 0) {
            cout << ' ';
        }
        cout << common[k];
    }
    cout << '\n';

    return 0;
}