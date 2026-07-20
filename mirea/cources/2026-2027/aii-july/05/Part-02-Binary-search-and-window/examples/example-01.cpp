// Пример: максимальная длина подотрезка положительных чисел с суммой не больше x.
// Решение: бинарный поиск по длине и проверка фиксированного окна.

#include <iostream>
#include <vector>

using namespace std;

bool check(const vector<int>& a, int k, long long x) {
    if (k == 0) {
        return true;
    }

    long long window_sum = 0;
    // Считаем сумму первого окна длины k.
    for (int i = 0; i < k; i++) {
        window_sum += a[i];
    }
    if (window_sum <= x) {
        return true;
    }

    for (int left = 0; left + k < (int)a.size(); left++) {
        // Переходим к следующему окну той же длины.
        window_sum -= a[left];
        window_sum += a[left + k];
        if (window_sum <= x) {
            return true;
        }
    }
    return false;
}

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

    int low = 0;
    int high = n + 1;
    // На полуинтервале [low, high): low подходит, high ещё не подходит.
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (check(a, mid, x)) {
            low = mid;
        } else {
            high = mid;
        }
    }

    cout << low << '\n';
    return 0;
}