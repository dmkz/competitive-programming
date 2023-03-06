#include <bits/stdc++.h>
using namespace std;
int main() {
    // чтение данных:
    int n, t; cin >> n >> t;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // решение задачи
    for (int i = 0; i < n; i++) {
        // сколько можем потратить времени на чтение в эти сутки:
        const int delta = min(t, 86400 - a[i]);
        t -= delta;
        // если прочитали полностью, то выводим ответ:
        if (t == 0) {
            cout << (i+1); // в 1-индексации
            return 0;
        }
    }
    assert(false);
}