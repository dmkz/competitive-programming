#include <bits/stdc++.h>
using namespace std;
int main() {
    // читаем данные, складывая первые элементы пар в массив `a`, а вторые - в массив `b`
    int k; cin >> k;
    vector<int> a, b;
    for (int i = 0, x, y; i < k; i++) {
        cin >> x >> y;
        a.push_back(x);
        b.push_back(y);
    }
    // сортируем и удаляем повторы в массивах a и b + выводим их содержимое:
    for (auto arr : {&a, &b}) {
        sort(arr->begin(), arr->end());
        arr->erase(unique(arr->begin(), arr->end()), arr->end());
        for (auto &item : *arr)
            cout << item << ' ';
        cout << '\n';
    }
}