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

// Очередь на минимум через монотонный deque. Для удобства реализуем в виде структуры.
template<typename T, typename Compare = std::less<T>>
struct MinQueue {
    // Данные храним как пары (значение, индекс)
    deque<pair<T, int>> data;
    // Добавление в конец (a[i], i):
    void push_back(T x, int i) {
        // сначала выталкиваем все >= элементы с конца:
        while (!data.empty() && Compare()(x, data.back().first))
            data.pop_back();
        // только теперь добавляем
        data.emplace_back(x, i);
    }
    // Удаление из начала очереди:
    void pop_front(int i) {
        // удаляем все элементы, у которых индекс <= i
        while (!data.empty() && data.front().second <= i)
            data.pop_front();
    }
    // Текущий минимум в окне:
    T getMin() const {
        assert(!data.empty());
        return data.front().first; // элемент в начале очереди и будет минимумом
    }
    // Какой будет минимум после добавления элемента x?
    T minAfterAdd(T x) const {
        return data.empty() ? x : min(x, getMin(), Compare());
    }

};

int64_t solve(int n, int R, const vector<int> &a) {
// Функция считает, сколько подотрезков [i, j], на которых max - min <= R.
    if (R < 0)
        return 0;
// Минимум и максимум будем хранить в монотонных deque:
    MinQueue<int> minQueue;
    MinQueue<int, greater<int>> maxQueue;
    
    int j = 0;
    int64_t answ = 0;
    for (int i = 0; i < n; i++) {
        // расширяем правую границу отрезка [i, j) до упора вправо:
        while (j < n) {
            // если после добавления нового элемента условие всё ещё выполняется:
            int newMax = maxQueue.minAfterAdd(a[j]);
            int newMin = minQueue.minAfterAdd(a[j]);
            if (newMax - newMin <= R) {
                // добавляем элемент и расширяем отрезок:
                minQueue.push_back(a[j], j);
                maxQueue.push_back(a[j], j);
                j++;
            } else
                break;
        }
        // Отрезок [i, j) - максимальный подходящий для этой левой границы
        if (i <= j)
            answ += j - i;
        // Удаляем элемент с индексом i:
        minQueue.pop_front(i);
        maxQueue.pop_front(i);
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
