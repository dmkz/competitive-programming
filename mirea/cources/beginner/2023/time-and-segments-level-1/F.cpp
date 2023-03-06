#include <bits/stdc++.h>
using namespace std;
int main() {
    // чтение данных
    int a, ta, b, tb, h, m;
    cin >> a >> ta >> b >> tb;
    scanf("%d:%d", &h, &m);
    m = 60 * h + m;
    // чтобы он встретился с автобусом, тот должен прибыть в пункт A
    // позже времени отправления и отправиться из пункта B раньше
    // времени прибытия. переберём автобусы и проверим каждое условие
    // автобусы из B отправляются в 05:00, 05:00 + b, 05:00 + 2*b, ...
    const int startA = m, finishA = m + ta;
    int answ{};
    for (int startB = 5 * 60; startB <= 23*60+59; startB += b) {
        const int finishB = startB + tb;
        answ += (startB < finishA && finishB > startA);
    }
    cout << answ;
}