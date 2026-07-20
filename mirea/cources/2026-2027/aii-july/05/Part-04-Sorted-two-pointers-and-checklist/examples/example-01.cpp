// Пример: существует ли пара элементов с суммой x.
// Ввод: n, x и массив a.
// Вывод: YES, если такая пара существует, иначе NO.

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long x;
    cin >> n >> x;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    int left = 0;
    int right = n - 1;
    bool ok = false;
    while (left < right) {
        long long sum = a[left] + a[right];
        if (sum == x) {
            ok = true;
            break;
        }
        if (sum < x) {
            // Левый элемент слишком мал, увеличиваем сумму.
            left++;
        } else {
            // Правый элемент слишком велик, уменьшаем сумму.
            right--;
        }
    }

    cout << (ok ? "YES" : "NO") << '\n';
    return 0;
}