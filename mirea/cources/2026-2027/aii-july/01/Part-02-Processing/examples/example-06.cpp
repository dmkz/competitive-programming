// Нахождение максимума, его количества и позиций в C++

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Чтение размера массива и его элементов
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (a.empty()) {
        return 0;
    }

    // Поиск ответа за один проход
    int mx = a[0];
    int cnt = 1;
    int first = 0;
    int last = 0;

    for (int i = 1; i < n; i++) {
        if (a[i] > mx) {
            mx = a[i];
            cnt = 1;
            first = i;
            last = i;
        } else if (a[i] == mx) {
            cnt++;
            last = i;
        }
    }

    // Поиск ответа с помощью стандартных функций
    auto mx_it = max_element(a.begin(), a.end());
    int stl_mx = *mx_it;
    int stl_cnt = count(a.begin(), a.end(), stl_mx);
    int stl_first = (int)(mx_it - a.begin());
    int stl_last = (int)a.size() - 1 - (int)(find(a.rbegin(), a.rend(), stl_mx) - a.rbegin());

    // Вывод ответа
    if (mx != stl_mx || cnt != stl_cnt || first != stl_first || last != stl_last) {
        return 1;
    }
    cout << mx << ' ' << cnt << ' ' << first << ' ' << last << '\n';
}