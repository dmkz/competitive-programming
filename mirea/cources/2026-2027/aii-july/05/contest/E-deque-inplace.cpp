// Искомое количество подотрезков массива с L <= max(a[i..j]) - min(a[i..j]) <= R обозначим
// как f(L, R). Тогда верно следующее: f(L, R) = f(0, R) - f(0, L-1) = f(R) - f(L-1). Поэтому
// будем считать сразу f(R): количество подотрезков с max(a[i..j]) - min(a[i..j]) <= R.
// Если мы зафиксируем левую границу отрезка, то справедлива монотонность:
// 1. min(a[i..j]) >= min(a[i..j+1]) <-- минимум при расширении вправо только уменьшается;
// 2. max(a[i..j]) <= max(a[i..j+1]) <-- максимум при расширении вправо лишь увеличивается.
// Поэтому мы поддерживаем в текущем окне два монотонных дека: для минимума и для максимума.
// Реализуем добавление в конец, удаление из начала, а также получение значения min/max.
// После этого мы используем метод двух указателей, чтобы посчитать количество отрезков
// для фиксированной левой границы i.
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
int64_t solve(int n, int R, const vector<int> &a) {
// Функция считает, сколько подотрезков [i, j], на которых max - min <= R.
    if (R < 0)
        return 0;
// Минимум и максимум будем хранить в монотонных deque:
    deque<pair<int,int>> minQueue, maxQueue;
    int j = 0;
    int64_t answ = 0;
    for (int i = 0; i < n; i++) {
        // расширяем правую границу отрезка [i, j) до упора вправо:
        while (j < n) {
            // если после добавления нового элемента условие всё ещё выполняется:
            int newMax = maxQueue.empty() ? a[j] : max(maxQueue.front().first, a[j]);
            int newMin = minQueue.empty() ? a[j] : min(minQueue.front().first, a[j]);
            if (newMax - newMin <= R) {
                // добавляем элемент и расширяем отрезок
                // сначала добавляем в очередь на минимум:
                while (!minQueue.empty() && minQueue.back().first > a[j])
                    minQueue.pop_back();
                minQueue.emplace_back(a[j], j);
                // затем в очередь на максимум:
                while (!maxQueue.empty() && maxQueue.back().first < a[j])
                    maxQueue.pop_back();
                maxQueue.emplace_back(a[j], j);
                j++;
            } else
                break;
        }
        // Отрезок [i, j) - максимальный подходящий для этой левой границы
        if (i <= j)
            answ += j - i;
        // Удаляем элемент с индексом i из обоих очередей:
        if (!minQueue.empty() && minQueue.front().second == i)
            minQueue.pop_front();
        if (!maxQueue.empty() && maxQueue.front().second == i)
            maxQueue.pop_front();
    }
    return answ;
}
void solve() {
    // читаем данные:
    int n, L, R;
    cin >> n >> L >> R;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // выводим ответ:
    cout << solve(n, R, a) - solve(n, L-1, a) << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
