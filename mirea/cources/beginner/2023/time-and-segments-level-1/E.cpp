#include <bits/stdc++.h>
using namespace std;
int main() {
    // чтение данных
    int n, sum{};
    cin >> n;
    for (int i = 0, a; i < n; i++) {
        cin >> a;
        sum += a;
    }
    // сначала решим все задачи, потом отправим их в одну и ту же секунду
    int m, answ = INT_MAX;
    cin >> m;
    while (m --> 0) {
        int L, R; cin >> L >> R;
        // если левая граница > sum, то придётся ждать
        if (L > sum) answ = min(answ, L);
        // иначе точно L <= sum, теперь если
        // правая граница >= sum, то ждать не придётся
        else if (R >= sum) answ = min(answ, sum);
    }
    // выводим ответ
    if (answ == INT_MAX) cout << "-1";
    else cout << answ;
}