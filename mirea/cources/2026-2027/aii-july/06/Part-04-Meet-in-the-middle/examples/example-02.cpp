// Пример: максимальная сумма подмножества, не превосходящая limit_sum.
// Решаем ту же задачу через meet-in-the-middle.

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Строим все суммы подмножеств для одной половины массива.
vector<long long> build_sums(const vector<long long>& part) {
    vector<long long> sums;
    int m = (int)part.size();
    sums.reserve(1 << m);
    for (int mask = 0; mask < (1 << m); mask++) {
        long long current_sum = 0;
        for (int i = 0; i < m; i++) {
            if ((mask >> i) & 1) current_sum += part[i];
        }
        sums.push_back(current_sum);
    }
    return sums;
}

int main() {
    int n;
    long long limit_sum;
    // Считываем массив и ограничение на сумму.
    cin >> n >> limit_sum;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Делим массив на две половины, чтобы перебирать их независимо.
    int mid = n / 2;
    vector<long long> left(a.begin(), a.begin() + mid);
    vector<long long> right(a.begin() + mid, a.end());

    // Генерируем все суммы отдельно для каждой половины.
    vector<long long> left_sums = build_sums(left);
    vector<long long> right_sums = build_sums(right);
    sort(right_sums.begin(), right_sums.end());

    long long best = 0;
    for (long long left_sum : left_sums) {
        if (left_sum > limit_sum) continue;

        // Ищем максимальную допустимую правую половину.
        long long need = limit_sum - left_sum;
        auto it = upper_bound(right_sums.begin(), right_sums.end(), need);
        if (it == right_sums.begin()) {
            best = max(best, left_sum);
            continue;
        }
        --it;
        best = max(best, left_sum + *it);
    }

    // Печатаем лучшую допустимую сумму.
    cout << best << '\n';
    return 0;
}