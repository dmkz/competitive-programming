// Пример: максимальная длина подотрезка положительных чисел с суммой не больше x.
// Решение: прямой проход двумя указателями.

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long x;
    cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int left = 0;
    long long window_sum = 0;
    int answer = 0;

    for (int right = 0; right < n; right++) {
        // Расширяем окно вправо.
        window_sum += a[right];
        // Пока окно плохое, сдвигаем левую границу.
        while (window_sum > x) {
            window_sum -= a[left];
            left++;
        }
        answer = max(answer, right - left + 1);
    }

    cout << answer << '\n';
    return 0;
}