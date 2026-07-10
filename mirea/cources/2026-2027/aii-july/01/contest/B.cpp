// Создадим два массива: один для нечётных элементов, а второй - для чётных.
// Отсортируем их отдельно, как это требуется в задаче, затем выведем их элементы
// на экран, чередуя массивы.

#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем данные и распределяем их в два вектора: нечётные и чётные
    int n; cin >> n;
    vector<int> odd, even;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        if (i % 2 == 1) odd.push_back(x);
        else even.push_back(x);
    }
    // сортируем оба вектора:
    sort(odd.begin(), odd.end(), greater<int>());
    sort(even.begin(), even.end());
    // чередуя, выводим ответ:
    int i = 0, j = 0;
    while (i < odd.size()) {
        // нечётный элемент:
        cout << odd[i] << ' ';
        i++;
        // чётный элемент:
        if (j < even.size()) {
            cout << even[j] << ' ';
            j++;
        }
    }
    cout << '\n';
}
int main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
