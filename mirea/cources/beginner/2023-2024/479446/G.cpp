#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем данные:
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // для каждого аннулирования надо найти ближайшую позицию, где этот пропуск потребуется
    vector<int> whenNeed(n+1, n), right(n, n);
    for (int i = n-1; i >= 0; i--) {
        if (a[i] > 0) {
            // первый тип, запрещает
            whenNeed[a[i]] = i;
        } else {
            // второй тип, аннулирует
            right[i] = whenNeed[-a[i]];
        }
    }
    // теперь мы используем эту информацию. Стартуя из i-й позиции, мы можем
    // дойти до минимальной проверки после аннулирования, то есть до
    // минимума из right[i], right[i+1], right[i+2], ..., right[n-1]
    int R = n;
    vector<int> answ(n);
    for (int i = n-1; i >= 0; i--) {
        R = min(R, right[i]);
        answ[i] = R - i;
    }
    // выводим ответ:
    for (int i = 0; i < n; i++)
        cout << answ[i] << ' ';
}
