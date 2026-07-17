// Пример: существует ли подотрезок с суммой 0.
// Ввод: n и массив чисел.
// Вывод: YES, если такой подотрезок есть, иначе NO.

#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Если два префикса равны, то между ними сумма равна нулю.
    set<long long> seen;
    seen.insert(0);

    long long sum = 0;
    for (long long value : a) {
        sum += value;
        if (seen.count(sum)) {
            cout << "YES\n";
            return 0;
        }
        seen.insert(sum);
    }

    cout << "NO\n";
    return 0;
}