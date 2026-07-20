// Пример: количество пар с суммой не больше s двумя указателями после сортировки.
// Ввод: число тестов, затем для каждого теста n, s и массив a.
// Вывод: для каждого теста число пар (i, j), i < j, таких что a[i] + a[j] <= s.

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    long long s;
    cin >> n >> s;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    int left = 0;
    int right = n - 1;
    long long answer = 0;
    while (left < right) {
        long long sum = a[left] + a[right];
        if (sum <= s) {
            // Для фиксированного left подходят все вторые индексы от left + 1 до right.
            answer += right - left;
            left++;
        } else {
            // Правый элемент слишком велик, уменьшаем сумму.
            right--;
        }
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests-- > 0) {
        solve();
    }

    return 0;
}