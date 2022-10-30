#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем и сортируем числа
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end());
    // для минимального должна быть пара и она больше него
    // если пары нет, то придётся удалить, и перейти к следующему числу
    // проверяем, есть ли пара, следующим образом: переберём степень
    // двойки (их 30 вариантов) и найдём нужный элемент бинпоиском
    // в отсортированном массиве `a`.
    int needRemove = 0;
    for (int i = 0; i < n; i++) {
        // ищем пару для a[i]
        bool pairExists = false;
        for (int d = 0; !pairExists && d <= 30; d++) {
            int power2d = (1 << d);
            int wantToFind = (power2d - a[i]);
            // вызываем бинпоиск: элементы на [begin, end) равны want:
            // https://ru.cppreference.com/w/cpp/algorithm/equal_range
            auto [begin, end] = equal_range(a.begin(), a.end(), wantToFind);
            int count = (end - begin);
            // мы могли найти случайно a[i], если want == a[i]
            if (count > 1 || (count == 1 && wantToFind != a[i]))
                pairExists = true;
        }
        if (!pairExists)
            needRemove++;
    }
    cout << needRemove << endl;
    return 0;
}