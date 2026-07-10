// Прочитаем массив чисел, скопируем его, отсортируем копию. Теперь для каждого
// элемента оригинального массива посчитаем, сколько элементов меньше него в
// отсортированной копии, с помощью бинарного поиска в отсортированном массиве.

#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем вектор
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // копируем и сортируем копию:
    vector<int> b = a;
    sort(b.begin(), b.end());
    // выводим ответ, считая количество меньших элементов в отсортированной копии:
    for (int i = 0; i < n; i++)
        cout << int(lower_bound(b.begin(), b.end(), a[i]) - b.begin()) << ' ';
    cout << '\n';
}
int main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
    return 0;
}
