// Сумма элементов массива в C++

#include <iostream>
#include <numeric>
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

    // Подсчёт суммы вручную
    long long manual_sum = 0;
    for (int x : a) {
        manual_sum += x;
    }

    // Подсчёт суммы через std::accumulate
    long long library_sum = accumulate(a.begin(), a.end(), 0LL);

    // Вывод ответа
    if (manual_sum != library_sum) {
        return 1;
    }
    cout << manual_sum << '\n';
}