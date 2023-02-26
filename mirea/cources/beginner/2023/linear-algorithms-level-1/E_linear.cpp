#include <bits/stdc++.h>
void setmin(auto &x, const auto &y) {
    if (y < x) x = y;
}
using namespace std;
int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // инициализируем вектор из ответов бесконечностями:
    const int INF = (int)1e9+7;
    vector<int> answer(n, INF);
    // будем хранить позицию ближайшего нуля
    // сначала цикл справа-налево:
    int zeroPosition = INF;
    for (int i = n-1; i >= 0; i--) {
        // если ноль, то обновляем ближайшую позицию нуля справа
        if (a[i] == 0)
            zeroPosition = i;
        // обновляем ответ
        setmin(answer[i], zeroPosition - i);
    }
    // теперь цикл слева-направо:
    zeroPosition = -INF;
    for (int i = 0; i < n; i++) {
        // если ноль, то обновляем ближайшую позицию нуля слева
        if (a[i] == 0)
            zeroPosition = i;
        // обновляем ответ
        setmin(answer[i], i - zeroPosition);
    }
    // выводим ответ
    for (int i = 0; i < n; i++)
        cout << answer[i] << ' ';
    cout << endl;
}