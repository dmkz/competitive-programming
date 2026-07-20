// Пример: минимум в каждом окне длины k через монотонную двустороннюю очередь.
// Ввод: n, k и массив a.
// Вывод: минимумы всех окон длины k слева направо.

#include <deque>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    deque<int> dq;
    // В двусторонней очереди храним только кандидатов на минимум.
    for (int i = 0; i < n; i++) {
        // Выкидываем из конца все элементы не лучше текущего.
        while (!dq.empty() && a[dq.back()] >= a[i]) {
            dq.pop_back();
        }
        dq.push_back(i);

        int left = i - k + 1;
        if (left < 0) {
            continue;
        }
        // Убираем из начала индексы, которые уже вышли из окна.
        while (!dq.empty() && dq.front() < left) {
            dq.pop_front();
        }

        if (left > 0) {
            cout << ' ';
        }
        cout << a[dq.front()];
    }
    cout << '\n';

    return 0;
}