// Стандартные алгоритмы бинарного поиска в C++

#include <algorithm>
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

    // Находим границы вхождений x и используем их для ответов на несколько вопросов
    auto lower_it = lower_bound(a.begin(), a.end(), x);
    auto upper_it = upper_bound(a.begin(), a.end(), x);
    bool found = binary_search(a.begin(), a.end(), x);
    auto [equal_left_it, equal_right_it] = equal_range(a.begin(), a.end(), x);

    int lower = (int)(lower_it - a.begin());
    int upper = (int)(upper_it - a.begin());
    bool found_by_lower = lower_it != a.end() && *lower_it == x;
    int equal_left = (int)(equal_left_it - a.begin());
    int equal_right = (int)(equal_right_it - a.begin());
    int equal_count = (int)(equal_right_it - equal_left_it);
    int less = lower;
    int equal = equal_count;
    int greater = (int)a.size() - upper;

    // Проверяем, что разные стандартные функции согласованы между собой
    if (found != found_by_lower || lower != equal_left || upper != equal_right) {
        return 1;
    }

    // Выводим позиции, факт наличия элемента и количества элементов по отношению к x
    cout << lower << ' ' << upper << '\n';
    cout << (found ? "YES" : "NO") << '\n';
    cout << equal_left << ' ' << equal_right << ' ' << equal_count << '\n';
    cout << less << ' ' << equal << ' ' << greater << '\n';
}