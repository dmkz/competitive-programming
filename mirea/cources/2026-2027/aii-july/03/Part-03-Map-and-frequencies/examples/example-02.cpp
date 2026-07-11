#include <cstdlib>
#include <iostream>
#include <map>
using namespace std;

int main() {
    srand(12345);
    map<int, int> cnt;
    const int n = 100;

    // Генерируем случайные числа и считаем остатки по модулю 10.
    for (int i = 0; i < n; i++) {
        int x = rand() % 10;
        cnt[x]++;
    }

    // Количество чисел в каждой группе.
    for (auto [key, value] : cnt) {
        cout << key << ": " << value << '\n';
    }

    // Минимальный и максимальный ключ.
    cout << "min key = " << cnt.begin()->first << '\n';
    cout << "max key = " << cnt.rbegin()->first << '\n';

    // Суммируем количества по ключам из диапазона [3, 7].
    int sum = 0;
    auto left = cnt.lower_bound(3);
    auto right = cnt.upper_bound(7);
    for (auto it = left; it != right; ++it) {
        sum += it->second;
    }
    cout << "sum on [3, 7] = " << sum << '\n';
}